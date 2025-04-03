# perceptron in C

resources, credits: [Tsoding](https://www.youtube.com/watch?v=PGSba51aRYU)

## Summary
**Basic Machine Learning Model in C**

Single neuron
- Resembled a perceptron using finite difference and gradient descant
- Trained to function as OR, AND, NAND, or NOR logic gate

Multi layer neuron
- Created a multi layer neurons (two layers) to resemble XOR logic gate
- comparison with seperately trained neurons (fixed structure)

## Explanation

**Logic behind multi layer neurons:**
A single neuron (perceptron) can only solve problems that are linearly separable, which means a single straight line seperates output classes. In terms of logic gate, output classess will be 0 and 1. 

For OR, AND, NOR, and NAND, output classes can be seperated by a single straight line (draw x1 and x2 axis and plot the values for visualization). However, for XOR, that is not possible. Thus, we include multiple layers of neurons to transform the input space (x1, x2 axis) such that output classes are linearly separable.  

Illustration of linearly separable data
![image](https://github.com/user-attachments/assets/dfaef9a5-d52a-4221-8a1f-434a8b4e3634)

**Seperately trained neurons**
xorGate-seperated.c shows three individual neurons trained with OR, NAND, AND data individually and combined to later to operate as XOR gate. But, obviously, this is not a neural network as there is no connection between neurons. 

Neural network has neurons that are interconnected. For XOR gate, we assumed two neurons in hidden layers will operate as OR, NAND gates. However, they do not. We cannot interpreate output of individual neuron to understand its purpose and functionality.  
