import glob, os, shutil

src_dir=os.path.join("..", "..", "Doxa")
dst_dir="Doxa"

os.makedirs(dst_dir, exist_ok=True)

# Copy only modified .HPP files, since the last run
files = glob.iglob(os.path.join(src_dir, "*.hpp"))
for src_file in files:
    if os.path.isfile(src_file):
        dst_file=os.path.join(dst_dir, os.path.basename(src_file))
        if not(os.path.isfile(dst_file)) or (os.stat(src_file).st_mtime - os.stat(dst_file).st_mtime > 0):
            shutil.copy2(src_file, dst_dir)
            print(f"Copying {src_file}")
