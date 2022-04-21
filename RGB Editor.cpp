// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: BMP Image Editor.cpp
// Last Modification Date: 02-04-2022
// Author1 and ID and Group: Aya Ali Hassan & 20210083 & A
// Author2 and ID and Group: Khaled Salah Abbas & 20211033 & A
// Author3 and ID and Group: Youssef Mohammed Morad & 20210485 & A
// Teaching Assistant: Eng. Nesma Mohamed & Eng. Yousra Ayman

#include <iostream>
#include <cstring>
#include "bmplib.cpp"


using namespace std;
unsigned char image[SIZE][SIZE][RGB];
unsigned char image2[SIZE][SIZE][RGB];
unsigned char new_image[SIZE][SIZE][RGB];

void loadImage();

void saveImage();

void BW();

void invert();

void merge();

void flip();

void detect_edges();

void darkandLight();

void rotate();

void filter_b();

void filter_c();

void filter_a();

void enlarge_image();

void shrink_image();

int main() {
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
        else if (tolower(option) == 's')
            saveImage();
        cout << "\n_______________________________________________________________\n";
    }

}

void loadImage() {
    char imageFileName[100];


    cout << "Please enter file name of the image to process"
            "\n>>";
    cin >> imageFileName;


    strcat(imageFileName, ".bmp");
    readRGBBMP(imageFileName, image);

}

//_________________________________________

void load_2_images() {
    char second_imageFileName[100];


    cout << "Please enter file name of the image you want to merge with."
            "\n>>";
    cin >> second_imageFileName;


    strcat(second_imageFileName, ".bmp");
    readRGBBMP(second_imageFileName, image2);

}

//_________________________________________

void saveImage() {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat(imageFileName, ".bmp");
    writeRGBBMP(imageFileName, image);
}

//_________________________________________
void BW() {
    double grey;
    for (auto &i: image) {
        for (auto &j: i) {
            grey = (j[0] * 0.3) + (j[1] * 0.59) + (j[2] * 0.11);
            for (unsigned char &k: j) {
                k = grey;
            }
        }
    }
    int sum = 0, avg;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                sum += image[i][j][k];
        }
    }
//here we got the average of the colors in the photo
    avg = sum / (SIZE * SIZE * RGB);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                if (image[i][j][k] > avg)
                    image[i][j][k] = 255;
                else {
                    image[i][j][k] = 0;
                }
        }
    }

}

//_________________________________________
void invert() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                image[i][j][k] = 255 - image[i][j][k];
            }
        }
    }
}

//_________________________________________
void merge() {}

//_________________________________________
void flip() {
    cout << "Flip (h)orizontally or (v)ertically ?"
            "\n>>";
    char choice;
    cin >> choice;
    if (tolower(choice) == 'v') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k)
                    new_image[i][j][k] = image[255 - i][j][k];
            }
        }
    } else if (tolower(choice) == 'h') {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k) {
                    new_image[i][j][k] = image[i][255 - j][k];
                }

            }
        }

    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                image[i][j][k] = new_image[i][j][k];
        }
    }
}

//_________________________________________
void detect_edges() {
    BW();
    for (int i = 1; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                new_image[i][j][k] = (image[i - 1][j - 1][k]) + (image[i + 1][j - 1][k]) + (image[i - 1][j][k])
                                     + (image[i][j][k] * -8) + (image[i + 1][j][k]) + (image[i - 1][j + 1][k])
                                     + (image[i][j + 1][k]) + (image[i + 1][j + 1][k]) + (image[i][j - 1][k]);
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                image[i][j][k] = new_image[i][j][k];
        }
    }

    for (auto &i: image) {
        for (auto &j: i) {
            for (unsigned char &k: j) {
                if (k >= 127) k = 0;
                else k = 255;
            }
        }
    }
}

//_________________________________________
void darkandLight() {}

//_________________________________________
void rotate() {
    int degree;
    cout << "Enter the degree you want the image be rotated by :";
    cin >> degree;
    if (degree == 270) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[255 - j][i][k] = image[i][j][k];
                }
            }
        }
    } else if (degree == 180) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[255 - i][255 - j][k] = image[i][j][k];
                }
            }
        }
    } else if (degree == 90) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[j][255 - i][k] = image[i][j][k];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                image[i][j][k] = new_image[i][j][k];
        }
    }
}

//_________________________________________
void shrink_image() {}

//_________________________________________
void enlarge_image() {
    int Quarter;
    cout << "Enter the quarter you want to enlarge :";
    cin >> Quarter;
    while (Quarter > 5 or Quarter < 0) {
        cout << "Enter a valid number :";
        cin >> Quarter;
    }
    if (Quarter == 1) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[i][j][k] = image[i / 2][j / 2][k];
                }
            }
        }
    } else if (Quarter == 2) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[i][256 - j][k] = image[i][256 - j / 2][k];
                }
            }
        }
    } else if (Quarter == 3) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[256 - i][j][k] = image[256 - i / 2][j / 2][k];
                }
            }
        }
    } else if (Quarter == 4) {
        for (int i = 0; i < 256; i++) {
            for (int j = 0; j < 256; j++) {
                for (int k = 0; k < 3; k++) {
                    new_image[256 - i][256 - j][k] = image[256 - i / 2][256 - j / 2][k];
                }
            }
        }
    }
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                image[i][j][k] = new_image[i][j][k];
        }
    }
}

//_________________________________________
void filter_a() {
    cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?"
            "\n>>";
    char choice;
    cin >> choice;
    if (choice == 'd') {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k)
                    image[i][j][k] = image[255 - i][j][k];
            }
        }
    } else if (choice == 'u') {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k)
                    image[255 - i][j][k] = image[i][j][k];
            }
        }
    } else if (choice == 'l') {

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k)
                    image[i][255 - j][k] = image[i][j][k];
            }
        }
    } else if (choice == 'r') {

        for (auto &i: image) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < 3; ++k)
                    i[j][k] = i[255 - j][k];
            }
        }
    }
}

//_________________________________________
void filter_b() {
    string order;
    unsigned char Quarter_1[SIZE][SIZE][RGB];
    unsigned char Quarter_2[SIZE][SIZE][RGB];
    unsigned char Quarter_3[SIZE][SIZE][RGB];
    unsigned char Quarter_4[SIZE][SIZE][RGB];
    cout << "Enter the order of quarters you want the image to be ordered by :" << endl;
    getline(cin >> ws, order, '\n');
    for (int i = 0; i < order.length(); i++) {
        if (order[i] == ' ') {
            order.erase(i, 1);
        }
    }
    for (int i = 0; i < 4; i++) {
        while (order[i] != '1' and order[i] != '2' and order[i] != '3' and order[i] != '4') {
            cout << "Please enter a valid order :" << endl;
            getline(cin >> ws, order, '\n');
            for (int i = 0; i < order.length(); i++) {
                if (order[i] == ' ') {
                    order.erase(i, 1);
                }
            }
        }
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 3; k++) {
                Quarter_1[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 0; i < 128; i++) {
        for (int j = 128; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                Quarter_2[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 0; j < 128; j++) {
            for (int k = 0; k < 3; k++) {
                Quarter_3[i][j][k] = image[i][j][k];
            }

        }
    }
    for (int i = 128; i < 256; i++) {
        for (int j = 128; j < 256; j++) {
            for (int k = 0; k < 3; k++) {
                Quarter_4[i][j][k] = image[i][j][k];
            }
        }
    }
    for (int k = 0; k < 4; k++) {
        if (k == 0) {
            for (int i = 0; i < 128; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (order[0] == '1') {
                            new_image[i][j][k] = Quarter_1[i][j][k];
                        } else if (order[0] == '2') {
                            new_image[i][j][k] = Quarter_2[i][128 + j][k];
                        } else if (order[0] == '3') {
                            new_image[i][j][k] = Quarter_3[128 + i][j][k];
                        } else if (order[0] == '4') {
                            new_image[i][j][k] = Quarter_4[128 + i][128 + j][k];
                        }
                    }
                }
            }

        } else if (k == 1) {
            for (int i = 0; i < 128; i++) {
                for (int j = 128; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (order[1] == '1') {
                            new_image[i][j][k] = Quarter_1[i][j - 128][k];
                        } else if (order[1] == '2') {
                            new_image[i][j][k] = Quarter_2[i][j][k];
                        } else if (order[1] == '3') {
                            new_image[i][j][k] = Quarter_3[128 + i][j - 128][k];
                        } else if (order[1] == '4') {
                            new_image[i][j][k] = Quarter_4[128 + i][j][k];
                        }
                    }
                }
            }


        } else if (k == 2) {
            for (int i = 128; i < 256; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (order[2] == '1') {
                            new_image[i][j][k] = Quarter_1[i - 128][j][k];
                        } else if (order[2] == '2') {
                            new_image[i][j][k] = Quarter_2[i - 128][128 + j][k];
                        } else if (order[2] == '3') {
                            new_image[i][j][k] = Quarter_3[i][j][k];
                        } else if (order[2] == '4') {
                            new_image[i][j][k] = Quarter_4[i][128 + j][k];
                        }
                    }
                }
            }
        } else if (k == 3) {
            for (int i = 128; i < 256; i++) {
                for (int j = 128; j < 256; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (order[3] == '1') {
                            new_image[i][j][k] = Quarter_1[i - 128][j - 128][k];
                        } else if (order[3] == '2') {
                            new_image[i][j][k] = Quarter_2[i - 128][j][k];
                        } else if (order[3] == '3') {
                            new_image[i][j][k] = Quarter_3[i][j - 128][k];
                        } else if (order[3] == '4') {
                            new_image[i][j][k] = Quarter_4[i][j][k];
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < 3; ++k)
                image[i][j][k] = new_image[i][j][k];
        }
    }
}

//_________________________________________
void filter_c() {}
//_________________________________________