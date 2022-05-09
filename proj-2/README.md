# Building project
In order to build project, you will need **Make** tool. 
Please run below commands in this order:   
 ```bash  
cd task_1 
make
```  
File `main` should appear in chosen directory.

# Creating svg from .dot file
In order to do that, you will need **Graphviz CLI** tool.  
Run command:  
```bash
dot file.dot -Tsvg -o outputFile.svg
```