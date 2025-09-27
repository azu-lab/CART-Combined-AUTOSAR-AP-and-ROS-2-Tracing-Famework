import sys

def insert_sections(template_path, insert_files, output_path, markers):
    # insert_files: [file1, file2, file3]
    # markers: ["// INSERT1", "// INSERT2", "// INSERT3"]
    inserts = []
    for f in insert_files:
        with open(f, 'r') as fin:
            inserts.append(fin.read())

    with open(template_path, 'r') as fin, open(output_path, 'w') as fout:
        content = fin.read()
        for marker, insert in zip(markers, inserts):
            content = content.replace(marker, insert)
        fout.write(content)

if __name__ == "__main__":
    # 例: python insert_sections.py template.c out.c a.txt b.txt c.txt d.txt
    if len(sys.argv) != 7:
        print("Usage: python insert_sections.py <template.c> <output.c> <insert1> <insert2> <insert3> <insert4>")
        sys.exit(1)
    template_path = sys.argv[1]
    output_path = sys.argv[2]
    insert_files = sys.argv[3:7]
    markers = ["// INSERT1", "// INSERT2", "// INSERT3", "// INSERT4"]
    insert_sections(template_path, insert_files, output_path, markers)