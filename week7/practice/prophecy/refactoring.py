from cs50 import SQL
import csv
from tqdm import tqdm

db = SQL("sqlite:///roster.db")

# db.execute("DROP TABLE assignments")
db.execute("DROP TABLE students")
# db.execute("DROP TABLE houses")

create_students_table = """
    CREATE TABLE students (
    id INTEGER,
    student_name TEXT,
    PRIMARY KEY(id)
);
"""

create_houses_table = """
    CREATE TABLE houses (
    id INTEGER,
    house TEXT,
    head TEXT,
    PRIMARY KEY(id)
);
"""

create_assignments_table = """
    CREATE TABLE assignments (
    id INTEGER,
    student_id INTEGER,
    house_id INTEGER,
    FOREIGN KEY(student_id) REFERENCES students(id)
    FOREIGN KEY(house_id) REFERENCES houses(id)
    PRIMARY KEY(id)
);
"""


# 建表
db.execute(create_assignments_table)
db.execute(create_students_table)
db.execute(create_houses_table)


file_path = '/workspaces/45230406/week7/practice/prophecy/students.csv'
with open(file_path) as file:
    reader = csv.DictReader(file)

    for row in tqdm(reader):
        # students 表
        db.execute("INSERT INTO students (student_name) VALUES (?)", row['student_name'])
        # student_id = db.lastrowid
        student_id = db.execute("SELECT last_insert_rowid() AS id")[0]['id']

        # 检查房间是否存在
        house_ids = db.execute("SELECT id FROM houses WHERE house = ?", row['house'])
        if house_ids:
            house_id = house_ids[0]['id']

        else:
            db.execute("INSERT INTO houses (house, head) VALUES (?, ?)", row['house'], row['head'])
            house_id = db.execute("SELECT last_insert_rowid() AS id")[0]['id']
        # 插入关联表
        db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", student_id, house_id)

print('executed!')

