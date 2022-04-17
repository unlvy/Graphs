# Building project
In order to build project, you will need **CMake** tool. 
Please run below commands in this order:   
 ```bash 
mkdir build  
cd build  
cmake ..  
make
```  
File 'proj-1.exe' should appear in 'build' directory.

# Creating svg from .gv file
In order to do that, you will need **Graphviz CLI** tool.  
Run command:  
```bash
dot file.gv -Tsvg -o outputFile.svg
```
