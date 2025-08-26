import os

# List of LaTeX compilation file extensions to delete
latex_extensions = [
    ".aux", ".bbl", ".blg", ".dvi", ".fdb_latexmk", ".fls", ".log", ".nlo",
    ".out", ".synctex.gz", ".tdo", ".toc"
]

main_file = "stm32.tex"

for root, dirs, files in os.walk("."):
    for file in files:
        # Skip the main file
        if file == main_file:
            continue
        # Check if the file is a LaTeX compilation file
        if any(file.endswith(ext) for ext in latex_extensions):
            file_path = os.path.join(root, file)
            try:
                os.remove(file_path)
                print(f"Deleted: {file_path}")
            except Exception as e:
                print(f"Error deleting {file_path}: {e}")