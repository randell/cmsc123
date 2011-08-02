/*
	Joseph Randell L. Benavidez
	CMSC 123 E-5L
	April 26, 2003
	chai356@yahoo.com
	
	Problem: Write a program that will read two matrices A and B (either from file or from online
	inputting, you will have top come up with an easy to follow inputting procedure OR interface),
	display them and calculate and display their product (or a message indicating that it is not defined).
	
	The running time will depend on three variables m, n and p.
	T(n) = 2*m*n*p + 9*m*n + 6*n*p + 4*m*p + 18*m + 9*n + 31
	O(n) = m*n*p 
*/

import java.io.*;

class Matrix {
	public static void main (String args[]) throws IOException {
		String input1,input2,input3,input4;
		int in1,in2,in3,in4;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		
		// Asks for the sizes of the two matrices
		System.out.print("\nPlease enter the number of rows for Matrix A: ");
		input1 = br.readLine();
		System.out.print("Please enter the number of columns for Matrix A: ");
		input2 = br.readLine();
		System.out.print("Please enter the number of rows for Matrix B: ");
		input3 = br.readLine();
		System.out.print("Please enter the number of columns for Matrix B: ");
		input4 = br.readLine();
		
			in1 = Integer.parseInt(input1);
			in2 = Integer.parseInt(input2);
			in3 = Integer.parseInt(input3);
			in4 = Integer.parseInt(input4);
			
		if (in2 == in3) {	// checks if the column of Matrix A is equal to the row of Matrix B
			System.out.println("");
			int m1[][] = new int[in1][in2];
			int m2[][] = new int[in2][in4];
			int m3[][] = new int[in1][in4];
			String mat = null;
			
			for (int i = 0; i < in1; i++)
				for (int j = 0; j < in4; j++)
					m3[i][j] = 0;	// initializes the cells of the resulting matrix
			
			////////// Asks for the values of the cells of Matrix A //////////
			for (int i = 0; i < in1; i++) {
				for (int j = 0; j < in2; j++) {
					System.out.print("Enter number for row " + (i + 1) + " and column " + (j + 1) + ": ");
					mat= br.readLine();
					if (mat != null)
						m1[i][j] = Integer.parseInt(mat);
					else
						m1[i][j] = 0;
				}
			}
			System.out.println("\nMatrix A\n");
			for (int i = 0; i < in1; i++) {
				for (int j = 0; j < in2; j++) {
					System.out.print(m1[i][j] + "\t");
				}
				System.out.println("");
			}
			System.out.println("");
			//////////////////////////////////////////////////////////////////
			
			////////// Asks for the values of the cells of Matrix B //////////
			for (int i = 0; i < in2; i++) {
				for (int j = 0; j < in4; j++) {
					System.out.print("Enter number for row " + (i + 1) + " and column " + (j + 1) + ": ");
					mat= br.readLine();
					if (mat != null) {
						m2[i][j] = Integer.parseInt(mat);
					}
					else
						m2[i][j] = 0;
				}
			}
			System.out.println("\nMatrix B\n");
			for (int i = 0; i < in2; i++) {
				for (int j = 0; j < in4; j++) {
					System.out.print(m2[i][j] + "\t");
				}
				System.out.println("");
			}
			//////////////////////////////////////////////////////////////////
			
			////////// Computes and prints the result of Matrix A * Matrix B //////////
			System.out.println("\nMatrix A x Matrix B\n");
			for (int i = 0; i < in1; i++)
				for (int j = 0; j < in4; j++)
					for (int k = 0; k < in2; k++)
						m3[i][j] += m1[i][k] * m2[k][j];
			
			for (int i = 0; i < in1; i++) {
				for (int j = 0; j < in4; j++) {
					System.out.print(m3[i][j] + "\t");
				}
				System.out.println("");
			}
			///////////////////////////////////////////////////////////////////////////
		}
		else	// Does not compute if the product of the two matrices are undefined
			System.out.println("Next time, please enter two valid matrices.");
	}	// end of main	
}	// end of class Matrix