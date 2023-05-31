# Лабораторная работа #12
*Автор: Харгелия Сергей*

## RIP

Решение собирается с помощью CMake. Для запуска решения в качестве единственного аргумента нужно передать путь до конфигурационного файла (пример можно посмотреть в файле [config.json](./config.json)). Программа выводит все промежуточные и финальные таблицы маршрутизации, также каждый маршрутизатор работает в отдельном потоке. 

Пример работы программы: 

```
[extraterrestrial@fedora build]$ ./rip ../config.json 
Simulation step 0 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 0 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 0 of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.1             192.168.0.1       0

Simulation step 1 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 1 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 2 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 0 of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.4             192.168.0.4       0

Simulation step 1 of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.3             192.168.0.3       1
192.168.0.4     192.168.0.4             192.168.0.4       0

Simulation step 2 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 1 of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.2             192.168.0.2       1
192.168.0.1     192.168.0.1             192.168.0.1       0

Simulation step 3 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 3 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 2 of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.3             192.168.0.3       1
192.168.0.4     192.168.0.2             192.168.0.3       2
192.168.0.4     192.168.0.4             192.168.0.4       0

Simulation step 4 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 2 of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.2             192.168.0.2       1
192.168.0.1     192.168.0.3             192.168.0.2       2
192.168.0.1     192.168.0.1             192.168.0.1       0

Simulation step 4 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 3 of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.3             192.168.0.3       1
192.168.0.4     192.168.0.2             192.168.0.3       2
192.168.0.4     192.168.0.4             192.168.0.4       0

Simulation step 5 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 3 of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.2             192.168.0.2       1
192.168.0.1     192.168.0.3             192.168.0.2       2
192.168.0.1     192.168.0.1             192.168.0.1       0

Simulation step 5 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 6 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 7 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 4 of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.3             192.168.0.3       1
192.168.0.4     192.168.0.1             192.168.0.3       3
192.168.0.4     192.168.0.2             192.168.0.3       2
192.168.0.4     192.168.0.4             192.168.0.4       0

Simulation step 6 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 4 of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.2             192.168.0.2       1
192.168.0.1     192.168.0.4             192.168.0.2       3
192.168.0.1     192.168.0.3             192.168.0.2       2
192.168.0.1     192.168.0.1             192.168.0.1       0

Simulation step 8 of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0

Simulation step 7 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Simulation step 8 of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Final state of router 192.168.0.1    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.1     192.168.0.2             192.168.0.2       1
192.168.0.1     192.168.0.4             192.168.0.2       3
192.168.0.1     192.168.0.3             192.168.0.2       2
192.168.0.1     192.168.0.1             192.168.0.1       0

Final state of router 192.168.0.4    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.4     192.168.0.3             192.168.0.3       1
192.168.0.4     192.168.0.1             192.168.0.3       3
192.168.0.4     192.168.0.2             192.168.0.3       2
192.168.0.4     192.168.0.4             192.168.0.4       0

Final state of router 192.168.0.3    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.3     192.168.0.4             192.168.0.4       1
192.168.0.3     192.168.0.2             192.168.0.2       1
192.168.0.3     192.168.0.1             192.168.0.2       2
192.168.0.3     192.168.0.3             192.168.0.3       0

Final state of router 192.168.0.2    
[Source IP]     [Destination IP]        [Next hop]        [Distance]
192.168.0.2     192.168.0.3             192.168.0.3       1
192.168.0.2     192.168.0.4             192.168.0.3       2
192.168.0.2     192.168.0.1             192.168.0.1       1
192.168.0.2     192.168.0.2             192.168.0.2       0
```
