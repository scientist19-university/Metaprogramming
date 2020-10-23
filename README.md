# Metaprogramming
Repository with labs for the Metaprogramming course

## Lab1 - JSON Formatter
### Requirements
In order to successfully compile and run the program you will need:
* Installed CMake started from the version 3.15.2
* MSVC C++ Compiler 2017

### Installation and usage (instruction for Windows)
1. Run terminal and navigate to `Metaprogramming\lab1\JSONFormatter\build`
2. Run consistently commands:  
`cmake -G "Visual Studio 15 2017" -S .. -B .`  
`cmake --build . --config Release`  
Alternatively, you can just run `build.bat` instead of commands running.
3. If the previous step is succeed, you will find few generated files in `Metaprogramming\lab1\JSONFormatter\build`  
Navigate to `Release` directory, you will find `JSONFormatter.exe`

### Command line options
```text
Options:
  --format <path-to-config> -(f | d | p) <path-to-file>     Format specified file/directory/project  
  -f <path-to-config> -(f | d | p) <path-to-file>           according to the provided template  
   
  --verify <path-to-config> -(f | d | p) <path-to-file>     Verify specified file/directory/project  
  -v <path-to-config> -(f | d | p) <path-to-file>           according to the provided template  
   
  --help                                                    Print help  
  -h
  ```  

### Configuration file (template)
Template is a file, where formatting parameters can be set.  
All parameters are optional, in case of some of it is not set, the default ones will be applied.  
  
The list of all parameters and its default values:  
```t
use_tabs false
indent_size 4

max_blank_lines 1
keep_indents_on_empty_lines false

space_before_comma false
space_after_comma false

space_before_colon false
space_after_colon true

wrap_objects true
wrap_arrays true

space_within_braces true
space_within_brackets true
```  
  
For better understanding, see `Metaprogramming\lab1\JSONFormatter\examples\config.ini`
