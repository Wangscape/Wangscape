# Introduction

Wangscape includes many different types of text, including English prose, C++,
Python, and JSON. This document provides style guidelines for text contributions
to the project. This applies to code, comments, documentation, and wiki pages,
not to discussions on issues, pull requests, and Gitter.

To the best of your ability, the contents of your pull requests should conform
to this style guide. If for any reason you are less able to conform to this guide
in your writing, your contributions are still very welcome. Any necessary corrections
can be made during the review process.

Some of the content already present in Wangscape may not conform to this style
guide. We welcome contributions which correct these errors, however minor.

If you feel this guide should be altered, please open an issue with your suggestions.
Possible changes to the style guide should only be discussed in dedicated spaces,
not in pull requests for features and bugfixes.

# Contents
0. [English](#english)
0. [C++](#c)
0. [Python](#python)
0. [JSON](#json)

# English

Wangscape is intended to be usable by non-programmers. All documentation related
to configuration of Wangscape and libnoise module groups should, to the fullest
extent possible, use language which is accessible to people without a background
in mathematics or computer science.

However, some understanding of JSON and libnoise modules will be necessary for a
user to take full advantage of Wangscape's configuration options, and Wangscape
should not duplicate existing efforts to document these technologies.

External links should be used wherever appropriate, especially to other projects
and their documentation and tutorials.

All documentation and comments should be clear and precise, while maintaining an
approachable tone.

## Capitalisation

* Anything named after Hao Wang should capitalise his name. This includes "Wangscape", 
"Wangview", and "corner Wang tile".
* libnoise should not be capitalised, even at the start of a sentence.

## Dialect
* Wangscape uses British English spellings and vocabulary.

# C++

## Naming conventions

### Case

* Names of `class`es, `struct`s, and other types should be in `PascalCase`.
* Names of `class` and `struct` methods should be in `camelCase`.
* Names of free functions should be in `camelCase`.
* Names of static const free variables should be in `UPPER_CASE`.
* Names of static const data variables should be in `UPPER_CASE`.
* Names of `class` and `struct` `public` data members which are non-const or non-static
should be in `camelCase`.
* Names of `class` and `struct` `protected and `private` data members which are
non-const or non-static should be in `mCamelCase` with an `m` prefix.
* Names of non-constructor function parameters should be in `snake_case`.
* Names of constructor parameters should be in `snake_case_` with a `_` postfix.
* Names of temporary function-local values should be in `snake_case`.
* Names of `namespace`s should be in `snake_case`.
* Names of template type parameters should be in `PascalCase`.
* Names of template value parameters should be in `PascalCase`.
* Names of enum values should be in `PascalCase`.
* Acronyms and initialisms in `PascalCase` and `camelCase` should be written in
upper case, even at the start of an identifier (`JSONData`).

### Filenames
Filenames are in `PascalCase`, with `.cpp` and `.h` extensions.

### General

* All identifiers should clearly and concisely describe the purpose of the associated
type, variable, function, or namespace. 
* Abbreviations may be used, but only when the meaning is still clear and a significant
number of characters is saved.
* Method parameters relating to a data member should not use synonyms, abbreviations,
or other tricks to avoid name collisions. In the rare cases when a method parameter
hides a data member, use `this->` to access the data member.

## Brackets and indentation

* Wangscape uses BSD (Allman) style braces, with 4 space indentation.
* Very short functions may be written on one line, if readability is improved.
* Single-statement code blocks may be written without braces, if readability is 
improved **and** it is unlikely that another statement will be added to the block.

## Long lines

* There is no hard limit on line length, but line breaks and appropriate indentation
should be used to make the code as readable as possible.

## Comments
* Comments should be used to clarify anything which is not obvious from the code
itself.
* Wangscape does not yet use a documentation generator, so there is no specific
format for class and function documentation comments.

## Modern C++
* C++14 features should be used wherever possible to make the code safer and more
readable.
* Raw pointers should only be used when absolutely necessary (for instance, if
library code requires raw pointers, or addresses must be compared).
* Some features of C++14 and C++17 may not yet be supported in the maintainers'
build environments; these should not be used.

## Other
* In pointer and reference declarations, there should be a space on the right side
of the `*` or `&`, and no space on the left.
* Do not use `using namespace x` declarations.

## Exemptions

Some code in Wangscape is meant to extend public APIs from other projects. Such
code may diverge from the Wangscape style guide in order to make its own public
API conform to the base code.

# Python

* Python code should conform to PEP8.
* `import *` should never be used.
* The content of IPython notebooks and associated Python modules
should be synchronised.
* Names of modules (and filenames) should be in `PascalCase`.
* Names of `class`es should be in `PascalCase`.
* Names of functions should be in `snake_case`.
* Names of class members should be in `snake_case`.
* Names of free variables should be in `snake_case`.

# JSON

* JSON code should conform to JSON Lint's style.
* Each indentation level should use a single tab character.
* JSON values should satisfy the appropriate schema:
  * Options files should conform to the options schema.
  * Module group files should conform to the module group schema.
  * Schemas should conform to draft 4 of the JSON metaschema.
