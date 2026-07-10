# MusicMachine

A C++ object-oriented programming project that models and manages multiple types of music through a shared class hierarchy.

This project was completed as a programming assignment for ITCS-2550 at Macomb Community College. It demonstrates inheritance, polymorphism, operator overloading, dynamic memory management, and unit testing.

## Features

- Represents chamber, orchestral, pop, jazz, rock, and electronic music
- Uses an abstract `Music` base class with specialized derived classes
- Calls type-specific behavior through virtual functions
- Stores different music objects in a single playlist
- Cycles through the playlist using an overloaded subscript operator
- Supports comparisons and type-specific operator overloads
- Includes automated tests using the doctest framework
- Checks for memory leaks when run with Microsoft Visual C++

## Object-Oriented Concepts

The project demonstrates:

- Abstract classes and pure virtual functions
- Inheritance
- Runtime polymorphism
- Constructors and destructors
- Dynamic allocation and cleanup
- Operator overloading
- Friend functions
- Enumerations
- Runtime type identification with `dynamic_cast`

## Music Types

| Class | Behavior |
|---|---|
| `Chamber` | Stores a musical key and cycles through available keys |
| `Orchestral` | Represents orchestral music |
| `Pop` | Implements equality and comparison operators |
| `Jazz` | Represents jazz music |
| `Rock` | Stores and modifies a loudness setting |
| `Electronic` | Stores BPM and supports incrementing or decrementing it |

## Project Structure

```text
cpp-musicmachine/
├── Main.cpp
├── doctest.h
├── TestData/
│   ├── JsonObject6a.json
│   ├── JsonObject7a.json
│   └── JsonObject8a.json
├── LICENSE
└── README.md
```
The included JSON files were supplied as course test data. The current implementation constructs its sample playlist directly in the program rather than loading it from those files.

## Running the Project

This assignment was originally developed for Microsoft Visual C++ and uses `_CrtSetDbgFlag` for memory-leak detection.

1. Clone the repository:

```bash
git clone https://github.com/karl-bucad/cpp-musicmachine.git
cd cpp-musicmachine
```

2. Open the project in Visual Studio or compile it in a compatible Microsoft C++ environment.

3. Run the generated executable. The doctest test suite will execute automatically and display the results.

## Example Output

```text
Chamber music in G key.
Playing: Symphony No. 5

Orchestral music playing.
Playing: Beethoven's 9th

Pop music playing.
Playing: Thriller
```

## Acknowledgments

Completed as coursework for ITCS-2550 at Macomb Community College. The assignment materials and original license were provided by ITCS-2550.

The doctest testing framework is maintained by its respective authors.

## License

The original course materials are distributed under the MIT License included in this repository.
