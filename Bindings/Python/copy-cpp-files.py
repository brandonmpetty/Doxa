import os.path
import shutil

if not os.path.exists("Doxa"):
    shutil.copytree("../../Doxa/", "Doxa")
