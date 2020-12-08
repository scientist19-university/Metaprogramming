# Lab2 JS code conventions analyzer and fixer


To use package install it from pipy:

https://pypi.org/project/jsconventionfixer/1.0.1/


Run 'pip install jsconventionfixer==1.0.1'


After successful installation project can be used command:
`jsconventionfixer (-v|-fx) -(p|d|f) <path>`

#### Command line options
```text
Options:
  -v, --verify                    Verify files without editing.
   
  -fx, --fix                      Rewrite files

  -d, --directory TEXT            Absolute or relative path to directory with 
                                  files to be fixed.
  
  -p, --project TEXT              Absolute or relative path to project with 
                                  files to be fixed.
                                  
  -f, --file TEXT                 Absolute or relative path to file to be fixed.

  -h, --help                      Show this message and exit.`
  ```
  *Note: any other input is equivalent to* `--help`

  