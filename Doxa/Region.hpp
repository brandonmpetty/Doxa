// Δoxa Binarization Framework
// License: CC0 2018, "Freely you have received; freely give." - Matt 10:8
#ifndef REGION_HPP
#define REGION_HPP


namespace Doxa
{
	/// <summary>
	/// A structure which denotes a specific area, or window, within an Image.
	/// Note that only Points are stored.  All other calls will be calculated.
	/// </summary>
	struct Region
	{
	public:
		struct Point
		{
			Point() {}
			Point(int x, int y) : x(x), y(y) {}

			bool operator==(const Point& rhs) const
			{
				return (x == rhs.x) && (y == rhs.y);
			}

			int x;
			int y;
		};

		Region() {}
		Region(const Point& upperLeft, const Point& bottomRight) : upperLeft(upperLeft), bottomRight(bottomRight) {}
		Region(int x1, int y1, int x2, int y2) : upperLeft(x1, y1), bottomRight(x2, y2) {}
		Region(int x1, int y1, int size) : upperLeft(x1, y1), bottomRight(x1 + size - 1, y1 + size - 1) {}
		Region(int width, int height) : upperLeft(0, 0), bottomRight(width - 1, height - 1) {}

		inline bool InRegion(const Region& region) const
		{
			return (region.upperLeft.x >= upperLeft.x &&
					region.upperLeft.y >= upperLeft.y &&
					region.bottomRight.x <= bottomRight.x &&
					region.bottomRight.y <= bottomRight.y);
		}

		inline int Width() const
		{
			return (bottomRight.x - upperLeft.x) + 1;
		}

		inline int Height() const
		{
			return (bottomRight.y - upperLeft.y) + 1;
		}

		inline int Area() const
		{
			return Width() * Height();
		}

		Point upperLeft;
		Point bottomRight;

		bool operator==(const Region& rhs) const
		{
			return (upperLeft == rhs.upperLeft) && (bottomRight == rhs.bottomRight);
		}
	};
}


#endif // REGION_HPP
