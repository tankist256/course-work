# Course Work - Student Database

## Project Milestones

- **Structure** - 17.10.2025
- **Database** - 22.10.2025
- **CLI Input** - 29.10.2025
- **Makefile** - 05.11.2025

## Libraries Used

- `stdlib` - Memory allocation and utilities
- `stdio` - Input/output operations

## Features

- Student structure with name, surname, group, and age
- Sorting functionality (by name, group, age, GPA)
- Dynamic and static array support
- Save/load student/parents data to/from files
- Command-line interface for manipulations with students/parents

## Usage

```bash
> git clone https://github.com/tankist256/course-work.git
> cd course-work
```

### Run program

```bash
> cd src/
> make 
> cd ..
> cd bin/
> ./program
```

### Check functionality

- from dir `completed-database/` copy `parents.txt` and `students.txt`
- paste copied files to dir `bin/`

### Project before make

```
course-work
├─ README.md
├─ completed-database
│  ├─ parents.txt
│  └─ students.txt
├─ include
│  ├─ database.c
│  ├─ database.h
│  ├─ mystring.c
│  ├─ mystring.h
│  ├─ parents.c
│  ├─ parents.h
│  ├─ sorts.crR
│  └─ sorts.h
└─ src
   ├─ Makefile
   └─ main.c

```
---
### Project after make
```
course-work
├─ README.md
├─ bin
│  └─ program
├─ completed-database
│  ├─ parents.txt
│  └─ students.txt
├─ include
│  ├─ database.c
│  ├─ database.h
│  ├─ mystring.c
│  ├─ mystring.h
│  ├─ parents.c
│  ├─ parents.h
│  ├─ sorts.c
│  └─ sorts.h
└─ src
   ├─ Makefile
   ├─ build
   │  ├─ database.o
   │  ├─ main.o
   │  ├─ mystring.o
   │  ├─ parents.o
   │  └─ sorts.o
   └─ main.c

```