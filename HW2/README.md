<h1 align="center"> INFA723 Homework 2 </h1>

<h3> Grading Criteria </h3>

- <i>Accuracy</i>:    
    - the solution meets specific requirements in the problem description;
    - the solution produces correct results; 
    - the procedures adopted in the solution are technically sound. 

- <i>Efficiency</i>:
    - efficiency will be one of the criteria when grading programing assignment. The solution should produce the desired results efficiently. 

- <i>Effort/ Neatness</i>:
    - the solution includes excellent effort, and all relate work is shown neatly and organized well. 

<div align="center">
    <br><br><i>Homework assignment feedback will be available through the DropBox folder on D2L.</i> 
</div>
<br><br>

<h2 align="center"> Track A <br></h2>

<i><sub> [view track a](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20A) </sub></i>

<h3> Lab Overview </h3>

This homework includes 4 labs listed as below:
- [Lab 1: Set up OpenSSL Testing Environment](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20A/Lab1) <i>(Optional if you already have an OpenSSL environment)</i>
- [Lab 2: OpenSSL Command Line](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20A/Lab2)
- [Lab 3: Send/Receive a File through a Socket Connection](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20A/Lab3)
- [Lab 4: Use OpenSSL Crypto Library to Encrypt/Decrypt a File and Send/Receive through a Socket Connection](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20A/Lab4)
<br><br>


<h3> Lab Preparation and Requirements </h3>

- If you already have an OpenSSL testing environment on your computer:
  - Skip Lab 1.
  - Open your Linux terminal and type the command:
    ```
    $ uname -a
    ```
  - Copy the output to a file and include it as part of your homework assignment.

- If you do not have a Linux machine or an OpenSSL environment:
  - Follow Lab 1 to set up an OpenSSL testing environment.
  - You can install a Linux virtual machine (e.g., using VMWare Workstation Player) on your Windows computer or request a Linux VM from the IALAB.
  - You need an OpenSSL environment before you can continue Lab 2, Lab 3, and Lab 4.

- For each lab (except Lab 1), there are question sections at the end of the labs. 
  - Answer all the questions in each lab.
  - The tutorials in the labs are for your practice.
  - You don’t need to include screenshots for your practice in the homework solution.
 

<h2 align="center"> Track B <br></h2>

<i><sub> [view track b](https://github.com/KieraConway/INFA723/tree/main/HW2/Track%20B) </sub></i>

1. <b>File Classification</b> <sub>&nbsp;&nbsp;(50 points)</sub> <br>  Three binary files are provided in this exercise: q1-file1, q2-file2, and q3-file3. These files include a firmware image, an encrypted file, and a compressed file.<br><br>
  a. Write a program to classify if a file is encrypted or not.<sub>&nbsp;&nbsp;(20 points)</sub><br>
  b. Explain what you use in the code to determine if a file is encrypted.<sub>&nbsp;&nbsp;(10 points)</sub><br>
  c. Identify each file’s category including firmware image, encrypted file, and compressed file.<sub>&nbsp;&nbsp;(10 points)</sub><br>
  d. If you can identify the compressed file, are you able to identify which algorithm is used to compress the file and un-compress the file.<sub>&nbsp;&nbsp;(10 points)</sub><br>

2. <b>Cipher Decryption</b> <sub>&nbsp;&nbsp;(50 points)</sub> <br> The file cipher.txt is encrypted using the AES algorithm with a key size of 192 and CBC mode of operation. The key and initial vector are provided below:
    ```
    key = 0294E7143C2DF135DAEFE9D74DF8BDCC488EDBA8FE5239A8
    iv = F3BC6E5B281EBF67210CD68837FFDE9A
    ```
      a. Write a program to decrypt the cipher.txt. <br>
      b. Submit a copy of the plaintext you decrypt.<br>
