
//--------------------------------------------------------
//Student Name: Vivek Kumar
// Student ID: 202051202
#include<stdio.h>
//--------------------------------------------------------
//encryption method is starting from here.
int *xor_array(int secret_key[], int plain_text[]) {
    //xoring the value of secret_key with plain_text
    int i;
   static int ans[16];
    for (i = 0; i < 16; i++) {
        ans[i] = plain_text[i] ^ secret_key[i];
        
    }
    
    
    return ans;
}
 //this is substitution function,it  is substituted the  output value of xor function 
    //according to x and sx array
int *substitute(int xor_arr[]){
   
    int i=0;
    int j=0;
    int index=0;
    static int ans[16];
    int x[16] = {0x00, 0x01, 0x02, 0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
    int sx[16]= {0x0e, 0x04, 0x0d, 0x01,0x02,0x0f,0x0b,0x08,0x03,0x0a,0x06,0x0c,0x05,0x09,0x00,0x07};
    for(i=0;i<16;i++){
        int curr=xor_arr[i];
        
        for(j=0;j<16;j++){
            if(curr==x[j]){
                index=j;
                break;
            }
        }
        xor_arr[i]=sx[index];
    }
    
    return xor_arr;
}
//this function is permuted the output value of substitution function according to per array.
int *permute(int sub_arr[]){
    
    int i=0;
    int index=0;
    static int final[16];
     int per[16]={0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
    for(i=0;i<16;i++){
       int temp=sub_arr[i];
        index=per[i];
        final[index]=temp;
    }
    return final;
}

//--------------------------------------------------------
//decryption methods are starting from here

//this function is permuted the encrypted output value from encryption functions
int *dpermute(int sub_arr[]){
    
    int i=0;
    int index=0;
    static int dfinal[16];
     int dper[16]={0,4,8,12,1,5,9,13,2,6,10,14,3,7,11,15};
    for(i=0;i<16;i++){
       int temp=sub_arr[i];
        index=dper[i];
        dfinal[index]=temp;
    }
    return dfinal;
}
//this metod is used for substitution for decryption functions
int *dsubstitute(int xor_arr[]){
    //this is substitution function,it  is substituted the  output value of xor function 
    //according to x and sx array
    int i=0;
    int j=0;
    int index=0;
    static int ans[16];
    int x[16] = {0x00, 0x01, 0x02, 0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
    int sx[16]= {0x0e, 0x04, 0x0d, 0x01,0x02,0x0f,0x0b,0x08,0x03,0x0a,0x06,0x0c,0x05,0x09,0x00,0x07};
    for(i=0;i<16;i++){
        int curr=xor_arr[i];
        
        for(j=0;j<16;j++){
            if(curr==sx[j]){
                index=j;
                break;
            }
        }
        xor_arr[i]=x[index];
    }
    
    return xor_arr;
}




int main() {
    //declaring the variables to use in upcoming code
    int i;
    int j;
    //declaring the array for plain_text input
    int plain_text[16];
    printf("Enter 16 bit hexadecimal plaintext: \n");
    for (i = 0; i < 16; i++) {
        scanf("%x", & plain_text [i]);
    }

    printf("The hexadecimal plaintext entered are: \n");
    for (i = 0; i < 16; i++) {
        printf("%x, ", plain_text [i]);
    }
    
    //declaring the array for secret_key input
    int secret_key[32];
    printf("\n");
    printf("Enter 32 bit secret key numbers: \n");
    for (j = 0; j < 32; j++) {
        // printf("Enter secret_key[%d]: ", i);
        scanf("%x", &secret_key[j]);
    }

    printf("The hexadecimal secret key entered are: \n");
    for (j = 0; j < 32; j++) {
        printf("%x, ",secret_key[j]);
    }
    printf("\n");
    int size=32;
    int window_size=16;
    int step_size=4;
    
    //sliding window code
    //declaring 5 array to store secret_key value according to given rule in lab assignment
    
    int array1[16];
    int array2[16];
    int array3[16];
    int array4[16];
    int array5[16];
    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
    int index4 = 0;
    int index5 = 0;
    
    for (int i = 0; i <= size - window_size; i += step_size) {
        for (int j = i; j < i + window_size; j++) {
            if (index1 < 16) {
                array1[index1++] = secret_key[j];
            }
            if (index2 < 16) {
                array2[index2++] = secret_key[j];
            }
            if (index3 < 16) {
                array3[index3++] = secret_key[j];
            }
            if (index4 < 16) {
                array4[index4++] = secret_key[j];
            }
            if (index5 < 16) {
                array5[index5++] = secret_key[j];
            }
        }
    }
    
    
    //--------------------------------------------------------
    //encryption for 1st round
    //this function gives the output value after xoring of plain_text with secret_key
    int *xor_arr1=xor_array(secret_key,plain_text);
    //this function gives the output of  substituted value of xor value 
    int *sub_arr1= substitute(xor_arr1);
    //this function gives the output of  permuted value of substituted value
    int *cipher1=permute(sub_arr1);
     
     //--------------------------------------------------------
     
     //--------------------------------------------------------
     //encryption for 2nd round
     
    int *xor_arr2= xor_array(secret_key,cipher1);
    int *sub_arr2= substitute(xor_arr2);
    int *cipher2=permute(sub_arr2);
     
     //--------------------------------------------------------
     
     
     //--------------------------------------------------------
     //encryption for 3rd round
     int *xor_arr3= xor_array(secret_key,cipher2);
     int *sub_arr3= substitute(xor_arr3);
     int *cipher3=permute(sub_arr3);
     
     
     
     //--------------------------------------------------------
     //encryption for 4th round
     int *xor_arr4= xor_array(secret_key,cipher3);
     int *cipher4= substitute(xor_arr4);
     //--------------------------------------------------------
     
     //--------------------------------------------------------
     //encryption for 5th round 
     
     int *cipher5= xor_array(secret_key,cipher4);
     //--------------------------------------------------------
     
     
     //--------------------------------------------------------
     //decryption for 5th round
     
     int *decrypted5=xor_array(secret_key,cipher5);
     
     //--------------------------------------------------------
     //decryption for 4th round
     int *dsub4=dsubstitute(decrypted5);
     int *dxor_arr4= xor_array(secret_key,dsub4);
     //--------------------------------------------------------
     
     //--------------------------------------------------------
     //decryption for 3rd round
     
     int *dperm3=dpermute(dxor_arr4);
     int *dsub_arr3= dsubstitute(dperm3);
     int *dxor_arr3= xor_array(secret_key,dsub_arr3);
     //--------------------------------------------------------
     
     //--------------------------------------------------------
     //decryption for 2nd round
     int *dperm2=dpermute(dxor_arr3);
     int *dsub_arr2= dsubstitute(dperm2);
     int *dxor_arr2= xor_array(secret_key,dsub_arr2);
     //--------------------------------------------------------
     
     //--------------------------------------------------------
     //decryption for 1st round
     int *dperm1=dpermute(dxor_arr2);
     int *dsub_arr1= dsubstitute(dperm1);
     int *dxor_arr1= xor_array(secret_key,dsub_arr1);
      
     
     printf("The hexadecimal plain_text after encryption and decryption are: \n");
    for (j = 0; j < 16; j++) {
        printf(" %x, ",  dxor_arr1[j]);
    }
     
    return 0;
}









