// Δoxa Binarization Framework
// License: CC0 2026, "Freely you have received; freely give." - Matt 10:8
#ifndef CONNECTEDCOMPONENTS_HPP
#define CONNECTEDCOMPONENTS_HPP

#include <algorithm>
#include <cstdint>
#include <vector>
#include "Image.hpp"
#include "Palette.hpp"
#include "Region.hpp"

// NOTE: This ConnectedComponents code is special purposed for generating Pseudo Weights.
namespace Doxa
{
	/// <summary>
	/// A single connected component representing a glyph, or part of a glyph.
	/// </summary>
	struct Component
	{
		int           label = 0;               // 1..N (0 is reserved for background)
		Region        bounds;                  // inclusive bounding box (upperLeft / bottomRight)
		int           pixelCount = 0;          // ink pixels (NOT bounds.Area(), which is the box)
		int           strokeWidth = 0;         // Gsw_fg: 2*floor(mean medial factor over the skeleton), set by the measure
	};

	/// <summary>
	/// The result of one labeling: the label image (0 = background, 1..N) plus
	/// the per-component records, indexed by label so items[L] is O(1) (items[0]
	/// is unused).  A plain value you pass around and range-iterate -- not a
	/// manager.  Cross-component relations (does a component of G overlap one of
	/// B) belong to the measure that consumes two of these, not here.
	/// </summary>
	class Components
	{
	public:
		int                    width = 0;
		int                    height = 0;
		std::vector<int>       labels;         // size width*height, 0 = background
		std::vector<Component> items;          // size N+1, items[0] unused

		int Count() const { return static_cast<int>(items.size()) - 1; }
		const Component& operator[](int label) const { return items[label]; }

		// Range-for visits real components only (skips the unused items[0]).
		std::vector<Component>::const_iterator begin() const { return items.begin() + 1; }
		std::vector<Component>::const_iterator end()   const { return items.end(); }
		std::vector<Component>::iterator begin() { return items.begin() + 1; }
		std::vector<Component>::iterator end()   { return items.end(); }

		/// <summary>
		/// Visits every label-owned pixel of every component in component -> row ->
		/// column order, passing the component, the (x, y) and the linear index i.  The
		/// window is clamped to the component's own bounds; the order matters for the
		/// in-place passes that read their already-updated up/left neighbors.
		/// </summary>
		template <typename Visitor>
		void ForEachPixel(Visitor&& visit) const
		{
			for (const Component& c : *this)
			{
				const int x0 = c.bounds.upperLeft.x, x1 = c.bounds.bottomRight.x;
				const int y0 = c.bounds.upperLeft.y, y1 = c.bounds.bottomRight.y;
				for (int y = y0; y <= y1; ++y)
				{
					const int row = y * width;
					for (int x = x0; x <= x1; ++x)
					{
						const int i = row + x;
						if (labels[i] == c.label) visit(c, x, y, i);
					}
				}
			}
		}
	};

	/// <summary>
	/// Two-pass union-find connected-component labeling, reading a ground-truth
	/// Image directly -- no intermediate mask, since the Image already is one.
	/// foreground selects the ink value (Palette::Black for DIBCO ground truth;
	/// pass Palette::White to label the inverted image for the background pass).
	/// connectivity8 sets the foreground rule; pass false (4-connectivity) when
	/// labeling an inverted image, to keep the 8/4 foreground/background
	/// topology consistent.
	/// </summary>
	class ConnectedComponents
	{
	public:
		static Components Generate(
			const Image& image,
			const Pixel8 foreground = Palette::Black,
			const bool connectivity8 = true)
		{
			return Generate(image.width, image.height, connectivity8,
				[&](const int i) { return image.data[i] == foreground; });
		}

		/// <summary>
		/// Labels straight from a 0/1 mask (target picks which value is foreground), so
		/// the background can be labeled from the foreground mask -- no inverted image.
		/// </summary>
		static Components Generate(
			const std::vector<uint8_t>& mask,
			const uint8_t target,
			const int width,
			const int height,
			const bool connectivity8 = true)
		{
			return Generate(width, height, connectivity8,
				[&](const int i) { return mask[i] == target; });
		}

	private:
		template <typename IsForeground>
		static Components Generate(
			const int width,
			const int height,
			const bool connectivity8,
			IsForeground isForeground)
		{
			const int size = width * height;

			Components result;
			result.width = width;
			result.height = height;
			result.labels.assign(size, 0);
			std::vector<int>& labels = result.labels;

			// Union-find over provisional labels (index 0 unused).
			std::vector<int> parent;
			parent.reserve(size / 2 + 2);
			parent.push_back(0);
			auto MakeSet = [&]() { parent.push_back(static_cast<int>(parent.size())); return static_cast<int>(parent.size()) - 1; };
			auto Find = [&parent](int a) { while (parent[a] != a) { parent[a] = parent[parent[a]]; a = parent[a]; } return a; };
			auto Union = [&](int a, int b) { a = Find(a); b = Find(b); if (a != b) parent[std::max(a, b)] = std::min(a, b); };

			// Pass 1: provisional labels from visited neighbors (W, N[, NW, NE]).
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const int idx = y * width + x;
					if (!isForeground(idx)) continue;

					int n[4];
					int cnt = 0;
					if (x > 0          && labels[idx - 1])         n[cnt++] = labels[idx - 1];
					if (y > 0          && labels[idx - width])     n[cnt++] = labels[idx - width];
					if (connectivity8)
					{
						if (y > 0 && x > 0         && labels[idx - width - 1]) n[cnt++] = labels[idx - width - 1];
						if (y > 0 && x < width - 1 && labels[idx - width + 1]) n[cnt++] = labels[idx - width + 1];
					}

					if (cnt == 0) { labels[idx] = MakeSet(); continue; }

					int m = Find(n[0]);
					for (int k = 1; k < cnt; ++k) m = std::min(m, Find(n[k]));
					labels[idx] = m;
					for (int k = 0; k < cnt; ++k) Union(m, n[k]);
				}
			}

			// Flatten roots to consecutive ids 1..N.
			std::vector<int> finalId(parent.size(), 0);
			int count = 0;
			for (int p = 1; p < static_cast<int>(parent.size()); ++p)
				if (Find(p) == p) finalId[p] = ++count;

			result.items.assign(count + 1, Component{});
			for (int L = 1; L <= count; ++L) result.items[L].label = L;

			// Pass 2: rewrite labels and accumulate per-component stats.
			for (int y = 0; y < height; ++y)
			{
				for (int x = 0; x < width; ++x)
				{
					const int idx = y * width + x;
					if (!labels[idx]) continue;

					const int L = finalId[Find(labels[idx])];
					labels[idx] = L;

					Component& c = result.items[L];
					if (c.pixelCount == 0)        // first sighting
						c.bounds = Region(x, y, x, y);
					++c.pixelCount;
					c.bounds.upperLeft.x   = std::min(c.bounds.upperLeft.x,   x);  // top y fixed by raster order
					c.bounds.bottomRight.x = std::max(c.bounds.bottomRight.x, x);
					c.bounds.bottomRight.y = std::max(c.bounds.bottomRight.y, y);
				}
			}

			return result;
		}
	};
}


#endif // CONNECTEDCOMPONENTS_HPP
