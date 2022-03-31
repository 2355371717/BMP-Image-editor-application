#include <iostream>
#include <cstring>
#include "bmplib.cpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#define RED     "\033[31m"      /* Red */


using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char new_image[SIZE][SIZE];

void loadImage();

void saveImage();

void BW();

void invert();

void merge();

void flip();

void detect_edges();

void save_new_Image();

void darkandLight();

void rotate();

void filter_b();

void filter_c();

void filter_a();

void enlarge_image();

void shrink_image();

int main() {
    cout << RED;
    cout << "Ahlan ya user ya habibi \uF04A\n";
    loadImage();
    while (true) {
        cout << "Please select a filter to apply or 0 to exit:\n"
                "1- Black & White Filter\n"
                "2- Invert Filter\n"
                "3- Merge Filter \n"
                "4- Flip Image\n"
                "5- Darken and Lighten Image \n"
                "6- Rotate Image\n"
                "7- Detect Image Edges \n"
                "8- Enlarge Image\n"
                "9- Shrink Image\n"
                "a- Mirror 1/2 Image\n"
                "b- Shuffle Image\n"
                "c- Blur Image\n"
                "s- Save the image to a file\n"
                "0- Exit\n"
                ">>";
        char option;
        cin >> option;

        if (tolower(option) == 'a')
            filter_a();
        else if (tolower(option) == 'b')
            filter_b();
        else if (tolower(option) == 'c')
            filter_c();
        else if (option == '1')
            BW();
        else if (option == '2')
            invert();
        else if (option == '3')
            merge();
        else if (option == '4')
            flip();
        else if (option == '5')
            darkandLight();
        else if (option == '6')
            rotate();
        else if (option == '7')
            detect_edges();
        else if (option == '8')
            enlarge_image();
        else if (option == '9')
            shrink_image();
        else if (option == '0')
            return 0;
        cout << "\n_______________________________________________________________\n";
    }

}

void load_2_images() {
    char seconed_imageFileName[100];

    // Get gray scale image file name

    cout << "Please enter file name of the image you want to merge with."
            "\n>>";
    cin >> seconed_imageFileName;

    // Add to it .bmp extension and load image
    strcat(seconed_imageFileName, ".bmp");
    readGSBMP(seconed_imageFileName, image2);
    //readGSBMP("Black.bmp", image);
}

void loadImage() {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Please enter file name of the image to process"
            "\n>>";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    readGSBMP(imageFileName, image);
    //readGSBMP("Black.bmp", image);
}

void save_new_Image() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << RED << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, new_image);
}


void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

void darkandLight() {
    cout << "What do you want to do?\n(D)arken the picture"
            "\n(L)ighten the picture\n>>";
    char choice;
    cin >> choice;
    if (toupper(choice) == 'D') {
        for (auto &i: image) {
            for (unsigned char &j: i) {
                int value = j;
                j = (value) / 2;
            }
        }
    } else if (toupper(choice) == 'L') {
        for (auto &i: image) {
            for (unsigned char &j: i) {
                int value = j;
                j = (value + 255) / 2;
            }
        }
    }
    saveImage();
}


void BW() {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            if (j > 127)
                j = 255;
            else
                j = 0;
        }
    }
    saveImage();
}

void merge() {
    load_2_images();
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            new_image[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }
    save_new_Image();
}

void rotate() {
    cout << "Rotate (90), (180) or (360) degrees?"
                    "\n>>";
    string choice;
    cin >> choice;
    if (choice == "180") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[255 - i][255 - j];
            }
        }
    } else if (choice == "90") {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[j][i] = image[255 - i][j];
            }
        }
    }
    save_new_Image();
}

void invert() {
    for (auto &i: image) {
        for (unsigned char &j: i) {
            j = 255 - j;
        }
    }
    saveImage();
}

void flip() {
    cout << "Flip (h)orizontally or (v)ertically ?"
                    "\n>>";
    char choice;
    cin >> choice;
    if (tolower(choice) == 'v') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[255 - i][j];
            }
        }
    } else if (tolower(choice) == 'h') {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                new_image[i][j] = image[i][255 - j];
            }
        }
    }
    save_new_Image();
}


void filter_A() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?"
                    "\n>>";
    char choice;
    cin >> choice;
    if (choice == 'd') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[255 - i][j];
            }
        }
    } else if (choice == 'u') {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[255 - i][j] = image[i][j];
            }
        }
    } else if (choice == 'l') {

        for (auto &i: image) {
            for (int j = 0; j < SIZE; j++) {
                i[255 - j] = i[j];
            }
        }
    } else if (choice == 'r') {

        for (auto &i: image) {
            for (int j = 0; j < SIZE; j++) {
                i[j] = i[255 - j];
            }
        }
    }
}

void filter_b() {

}

void filter_c() {

}

void filter_a() {

}

void enlarge_image() {

}

void shrink_image() {

}

void detect_edges() {

}