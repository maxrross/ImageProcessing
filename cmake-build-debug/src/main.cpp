#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
#include "image.h"

void getDataFromBinaryFile(string filePath, image& currentImage, Header& headerObject);
void writeData(string filename, image& currentImage, Header& headerObject);
void writeDataMultiply(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader);
void writeDataSubtract(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader);
void writeDataScreen(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader);
void writeDataOverlay(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader);
bool compareFiles(image& currentImage, Header& headerObject, image& pattern, Header& patternHeader);
void splitFile(image& currentImage, Header& headerObject);
void compactFile(image& imageOne, Header& HeaderOne, image& imageTwo, Header& HeaderTwo,image& imageThree, Header& HeaderThree);
void rotateFile(image& currentImage, Header& headerObject);


int main() {
    //inputting both files for task 1
    image layer1;
    image pattern1;
    Header header1;
    Header patternHeader1;
    getDataFromBinaryFile("input/layer1", layer1, header1);
    getDataFromBinaryFile("input/pattern1", pattern1, patternHeader1);
    //outputting task 1
    writeDataMultiply("part1", layer1, header1, pattern1, patternHeader1);
    //testing
    image p1;
    Header p1h;
    image p1ex;
    Header p1exh;
    getDataFromBinaryFile("output/part1", p1, p1h);
    getDataFromBinaryFile("examples/EXAMPLE_part1", p1ex, p1exh);
    cout << "Test 1 Passed?: "<< compareFiles(p1, p1h, p1, p1exh) <<endl;

    //inputting files for task 2
    image layer2;
    image car;
    Header header2;
    Header carHeader;
    getDataFromBinaryFile("input/layer2", layer2, header2);
    getDataFromBinaryFile("input/car", car, carHeader);
    //outputting task 2
    writeDataSubtract("part2", layer2, header2, car, carHeader);
    //testing
    image p2;
    Header p2h;
    image p2ex;
    Header p2exh;
    getDataFromBinaryFile("output/part2", p2, p2h);
    getDataFromBinaryFile("examples/EXAMPLE_part2", p2ex, p2exh);
    cout << "Test 2 Passed?: "<< compareFiles(p2, p2h, p2ex, p2exh) <<endl;

    //inputting task 3
    image text1;
    image pattern2;
    Header textHeader1;
    Header patternHeader2;
    getDataFromBinaryFile("input/text", text1, textHeader1);
    getDataFromBinaryFile("input/pattern2", pattern2, patternHeader2);
    //tasks for task 3
    writeDataMultiply("temp", layer1, header1, pattern2, patternHeader2);
    //getting the temp file
    image temp;
    Header tempHeader;
    getDataFromBinaryFile("output/temp", temp, tempHeader);
    //using the temp file to make part 3
    writeDataScreen("part3", text1, textHeader1, temp, tempHeader);
    //testing
    image p3;
    Header p3h;
    image p3ex;
    Header p3exh;
    getDataFromBinaryFile("output/part3", p3, p3h);
    getDataFromBinaryFile("examples/EXAMPLE_part3", p3ex, p3exh);
    cout << "Test 3 Passed?: "<< compareFiles(p3, p3h, p3ex, p3exh) <<endl;

    //tasks for task 4
    image circles;
    Header circlesHeader;
    image temp2;
    Header tempHeader2;
    getDataFromBinaryFile("input/circles", circles, circlesHeader);
    writeDataMultiply("temp2", layer2, header2, circles, circlesHeader);
    getDataFromBinaryFile("output/temp2", temp2, tempHeader2);
    writeDataSubtract("part4",pattern2, patternHeader2,temp2,tempHeader2);
    //testing
    image p4;
    Header p4h;
    image p4ex;
    Header p4exh;
    getDataFromBinaryFile("output/part4", p4, p4h);
    getDataFromBinaryFile("examples/EXAMPLE_part4", p4ex, p4exh);
    cout << "Test 4 Passed?: "<< compareFiles(p4, p4h, p4ex, p4exh) <<endl;

    //task 5
    writeDataOverlay("part5", pattern1, patternHeader1, layer1, header1);
    //testing
    image p5;
    Header p5h;
    image p5ex;
    Header p5exh;
    getDataFromBinaryFile("output/part5", p5, p5h);
    getDataFromBinaryFile("examples/EXAMPLE_part5", p5ex, p5exh);
    cout << "Test 5 Passed?: "<< compareFiles(p5, p5h, p5ex, p5exh) <<endl;

    //task 6
    for (int i=0; i<carHeader.height * carHeader.width; i++){
        int currentG=(int)car.pixels.at(i).green;
        currentG+=200;
        if (currentG>255){
            currentG=255;
        }
        car.pixels.at(i).green= (unsigned char)currentG;
    }
    writeData("part6", car, carHeader);
    //testing
    image p6;
    Header p6h;
    image p6ex;
    Header p6exh;
    getDataFromBinaryFile("output/part6", p6, p6h);
    getDataFromBinaryFile("examples/EXAMPLE_part6", p6ex, p6exh);
    cout << "Test 6 Passed?: "<< compareFiles(p6, p6h, p6ex, p6exh) <<endl;

    //task 7
    image car2;
    Header carHeader2;
    getDataFromBinaryFile("input/car", car2, carHeader2);
    for (int i=0; i<carHeader2.height * carHeader2.width; i++){
        int currentR=(int)car2.pixels.at(i).red;
        int currentB=(int)car2.pixels.at(i).blue;
        currentR*=4;
        currentB*=0;
        if (currentR>255){
            currentR=255;
        }
        car2.pixels.at(i).red= (unsigned char)currentR;
        car2.pixels.at(i).blue= (unsigned char)currentB;
    }
    writeData("part7", car2, carHeader2);
    //testing
    image p7;
    Header p7h;
    image p7ex;
    Header p7exh;
    getDataFromBinaryFile("output/part7", p7, p7h);
    getDataFromBinaryFile("examples/EXAMPLE_part7", p7ex, p7exh);
    cout << "Test 7 Passed?: "<< compareFiles(p7, p7h, p7ex, p7exh) <<endl;

    //task 8
    image car3;
    Header carHeader3;
    getDataFromBinaryFile("input/car", car3, carHeader3);
    splitFile(car3, carHeader3);
    //testing
    image p8_r;
    Header p8_rh;
    image p8_rex;
    Header p8_rexh;
    getDataFromBinaryFile("output/part8_r", p8_r, p8_rh);
    getDataFromBinaryFile("examples/EXAMPLE_part8_r", p8_rex, p8_rexh);
    cout << "Test 8 Red Passed?: "<< compareFiles(p8_r, p8_rh, p8_rex, p8_rexh) <<endl;
    image p8_g;
    Header p8_gh;
    image p8_gex;
    Header p8_gexh;
    getDataFromBinaryFile("output/part8_g", p8_g, p8_gh);
    getDataFromBinaryFile("examples/EXAMPLE_part8_g", p8_gex, p8_gexh);
    cout << "Test 8 Green Passed?: "<< compareFiles(p8_g, p8_gh, p8_gex, p8_gexh) <<endl;
    image p8_b;
    Header p8_bh;
    image p8_bex;
    Header p8_bexh;
    getDataFromBinaryFile("output/part8_b", p8_b, p8_bh);
    getDataFromBinaryFile("examples/EXAMPLE_part8_b", p8_bex, p8_bexh);
    cout << "Test 8 Blue Passed?: "<< compareFiles(p8_b, p8_bh, p8_bex, p8_bexh) <<endl;

    //task 9
    image lr;
    image lb;
    image lg;
    Header lrh;
    Header lbh;
    Header lgh;
    getDataFromBinaryFile("input/layer_red", lr, lrh);
    getDataFromBinaryFile("input/layer_blue", lb, lbh);
    getDataFromBinaryFile("input/layer_green", lg, lgh);
    //insert in rgb format
    compactFile(lr, lrh, lg, lgh, lb, lbh);
    //testing
    image p9;
    Header p9h;
    image p9ex;
    Header p9exh;
    getDataFromBinaryFile("output/part9", p9, p9h);
    getDataFromBinaryFile("examples/EXAMPLE_part9", p9ex, p9exh);
    cout << "Test 9 Passed?: "<< compareFiles(p9, p9h, p9ex, p9exh) <<endl;

    //part10
    image text2;
    Header textHeader2;
    getDataFromBinaryFile("input/text2", text2, textHeader2);
    rotateFile(text2, textHeader2);
    //testing
    image p10;
    Header p10h;
    image p10ex;
    Header p10exh;
    getDataFromBinaryFile("output/part10", p10, p10h);
    getDataFromBinaryFile("examples/EXAMPLE_part10", p10ex, p10exh);
    cout << "Test 10 Passed?: "<< compareFiles(p10, p10h, p10ex, p10exh) <<endl;
    return 0;
}

bool compareFiles(image& currentImage, Header& headerObject, image& pattern, Header& patternHeader){
    for (int i=0; i<headerObject.width* headerObject.height; i++){
        if ((double)currentImage.pixels.at(i).red!=(double)pattern.pixels.at(i).red){
            cout << "Test failed at RED pixel: "<<i<<endl;
            cout << "RED Pixel value of your image was: " <<(double)currentImage.pixels.at(i).red <<endl;
            cout << "RED Pixel value of other image was: " <<(double)pattern.pixels.at(i).red <<endl;
            return false;
        }
        if ((double)currentImage.pixels.at(i).green!=(double)pattern.pixels.at(i).green){
            cout << "Test failed at GREEN pixel: "<<i<<endl;
            cout << "GREEN Pixel value of your image was: " <<(double)currentImage.pixels.at(i).green <<endl;
            cout << "GREEN Pixel value of other image was: " <<(double)pattern.pixels.at(i).green <<endl;
            return false;
        }
        if ((double)currentImage.pixels.at(i).blue!=(double)pattern.pixels.at(i).blue){
            cout << "Test failed at BLUE pixel: "<<i<<endl;
            cout << "BLUE Pixel value of your image was: " <<(double)currentImage.pixels.at(i).blue <<endl;
            cout << "BLUE Pixel value of other image was: " <<(double)pattern.pixels.at(i).blue <<endl;
            return false;
        }
    }
    return true;
}

void getDataFromBinaryFile(string filename, image& currentImage, Header& headerObject){
    ifstream inFile(filename+".tga", ios_base::binary);
    inFile.read((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    inFile.read((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    inFile.read((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    inFile.read((char*)&headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    inFile.read((char*)&headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    inFile.read((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    inFile.read((char*)&headerObject.xOrigin, sizeof(headerObject.xOrigin));
    inFile.read((char*)&headerObject.yOrigin, sizeof(headerObject.yOrigin));
    inFile.read((char*)&headerObject.width, sizeof(headerObject.width));
    inFile.read((char*)&headerObject.height, sizeof(headerObject.height));
    inFile.read((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    inFile.read((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int i=0; i<(headerObject.height * headerObject.width); i++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        inFile.read((char *)&blue, sizeof(blue));
        inFile.read((char *)&green, sizeof(green));
        inFile.read((char *)&red, sizeof(red));
        pixel newPixel = pixel(red,green,blue);
        newPixel.red = red;
        newPixel.blue=blue;
        newPixel.green=green;
//        if (i==0) {
//            cout << (int) red << " " << (int) green << " " << (int) blue << endl;
//        }
        currentImage.pixels.push_back(newPixel);
    }
//    cout << (int)currentImage.pixels[0].red <<endl;
//    cout << (int)currentImage.pixels[0].green<<endl;
//    cout << (int)currentImage.pixels[0].blue<<endl;
}

void writeData(string name, image& currentImage, Header& headerObject) {
    ofstream myfile("output/"+name+".tga", ios_base::binary);
    myfile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    myfile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    myfile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    myfile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    myfile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    myfile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    myfile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    myfile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    myfile.write((char *) &headerObject.width, sizeof(headerObject.width));
    myfile.write((char *) &headerObject.height, sizeof(headerObject.height));
    myfile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    myfile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        green = currentImage.pixels.at(j).green;
        blue = currentImage.pixels.at(j).blue;
        red = currentImage.pixels.at(j).red;
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}

void writeDataMultiply(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader) {
    ofstream myfile("output/"+name+".tga", ios_base::binary);
    myfile.write((char*)&patternHeader.idLength, sizeof(patternHeader.idLength));
    myfile.write((char*)&patternHeader.colorMapType, sizeof(patternHeader.colorMapType));
    myfile.write((char*)&patternHeader.dataTypeCode, sizeof(patternHeader.dataTypeCode));
    myfile.write((char *) &patternHeader.colorMapOrigin, sizeof(patternHeader.colorMapOrigin));
    myfile.write((char *) &patternHeader.colorMapLength, sizeof(patternHeader.colorMapLength));
    myfile.write((char*)&patternHeader.colorMapDepth, sizeof(patternHeader.colorMapDepth));
    myfile.write((char *) &patternHeader.xOrigin, sizeof(patternHeader.xOrigin));
    myfile.write((char *) &patternHeader.yOrigin, sizeof(patternHeader.yOrigin));
    myfile.write((char *) &patternHeader.width, sizeof(patternHeader.width));
    myfile.write((char *) &patternHeader.height, sizeof(patternHeader.height));
    myfile.write((char*)&patternHeader.bitsPerPixel, sizeof(patternHeader.bitsPerPixel));
    myfile.write((char*)&patternHeader.imageDescriptor, sizeof(patternHeader.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char red = (unsigned char) round(((double)currentImage.pixels.at(j).red*(double)pattern.pixels.at(j).red) / 255.0);
        unsigned char green = (unsigned char) round(((double)currentImage.pixels.at(j).green*(double)pattern.pixels.at(j).green) / 255.0);
        unsigned char blue = (unsigned char) round(((double)currentImage.pixels.at(j).blue*(double)pattern.pixels.at(j).blue) / 255.0);
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}

void writeDataSubtract(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader) {
    ofstream myfile("output/"+name+".tga", ios_base::binary);
    myfile.write((char*)&patternHeader.idLength, sizeof(patternHeader.idLength));
    myfile.write((char*)&patternHeader.colorMapType, sizeof(patternHeader.colorMapType));
    myfile.write((char*)&patternHeader.dataTypeCode, sizeof(patternHeader.dataTypeCode));
    myfile.write((char *) &patternHeader.colorMapOrigin, sizeof(patternHeader.colorMapOrigin));
    myfile.write((char *) &patternHeader.colorMapLength, sizeof(patternHeader.colorMapLength));
    myfile.write((char*)&patternHeader.colorMapDepth, sizeof(patternHeader.colorMapDepth));
    myfile.write((char *) &patternHeader.xOrigin, sizeof(patternHeader.xOrigin));
    myfile.write((char *) &patternHeader.yOrigin, sizeof(patternHeader.yOrigin));
    myfile.write((char *) &patternHeader.width, sizeof(patternHeader.width));
    myfile.write((char *) &patternHeader.height, sizeof(patternHeader.height));
    myfile.write((char*)&patternHeader.bitsPerPixel, sizeof(patternHeader.bitsPerPixel));
    myfile.write((char*)&patternHeader.imageDescriptor, sizeof(patternHeader.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char red = (unsigned char) round(((double)pattern.pixels.at(j).red-(double)currentImage.pixels.at(j).red));
        unsigned char green = (unsigned char) round(((double)pattern.pixels.at(j).green-(double)currentImage.pixels.at(j).green));
        unsigned char blue = (unsigned char) round(((double)pattern.pixels.at(j).blue-(double)currentImage.pixels.at(j).blue));
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}

void writeDataScreen(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader) {
    ofstream myfile("output/"+name+".tga", ios_base::binary);
    myfile.write((char*)&patternHeader.idLength, sizeof(patternHeader.idLength));
    myfile.write((char*)&patternHeader.colorMapType, sizeof(patternHeader.colorMapType));
    myfile.write((char*)&patternHeader.dataTypeCode, sizeof(patternHeader.dataTypeCode));
    myfile.write((char *) &patternHeader.colorMapOrigin, sizeof(patternHeader.colorMapOrigin));
    myfile.write((char *) &patternHeader.colorMapLength, sizeof(patternHeader.colorMapLength));
    myfile.write((char*)&patternHeader.colorMapDepth, sizeof(patternHeader.colorMapDepth));
    myfile.write((char *) &patternHeader.xOrigin, sizeof(patternHeader.xOrigin));
    myfile.write((char *) &patternHeader.yOrigin, sizeof(patternHeader.yOrigin));
    myfile.write((char *) &patternHeader.width, sizeof(patternHeader.width));
    myfile.write((char *) &patternHeader.height, sizeof(patternHeader.height));
    myfile.write((char*)&patternHeader.bitsPerPixel, sizeof(patternHeader.bitsPerPixel));
    myfile.write((char*)&patternHeader.imageDescriptor, sizeof(patternHeader.imageDescriptor));

    for (unsigned int j = 0; j < (patternHeader.width * patternHeader.height); j++) {
        //C=1-(1-A)*(1-B)
        unsigned char red = (unsigned char)round((1.0 - ((1.0 - (double)currentImage.pixels.at(j).red / 255.0) * (1.0 - (double)pattern.pixels.at(j).red / 255.0))) * 255.0);
        unsigned char green = (unsigned char)round((1.0 - ((1.0 - (double)currentImage.pixels.at(j).green / 255.0) * (1.0 - (double)pattern.pixels.at(j).green / 255.0))) * 255.0);
        unsigned char blue = (unsigned char)round((1.0 - ((1.0 - (double)currentImage.pixels.at(j).blue / 255.0) * (1.0 - (double)pattern.pixels.at(j).blue / 255.0))) * 255.0);
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}

void writeDataOverlay(string name, image& currentImage, Header& headerObject, image& pattern, Header& patternHeader) {
    ofstream myfile("output/"+name+".tga", ios_base::binary);
    myfile.write((char*)&patternHeader.idLength, sizeof(patternHeader.idLength));
    myfile.write((char*)&patternHeader.colorMapType, sizeof(patternHeader.colorMapType));
    myfile.write((char*)&patternHeader.dataTypeCode, sizeof(patternHeader.dataTypeCode));
    myfile.write((char *) &patternHeader.colorMapOrigin, sizeof(patternHeader.colorMapOrigin));
    myfile.write((char *) &patternHeader.colorMapLength, sizeof(patternHeader.colorMapLength));
    myfile.write((char*)&patternHeader.colorMapDepth, sizeof(patternHeader.colorMapDepth));
    myfile.write((char *) &patternHeader.xOrigin, sizeof(patternHeader.xOrigin));
    myfile.write((char *) &patternHeader.yOrigin, sizeof(patternHeader.yOrigin));
    myfile.write((char *) &patternHeader.width, sizeof(patternHeader.width));
    myfile.write((char *) &patternHeader.height, sizeof(patternHeader.height));
    myfile.write((char*)&patternHeader.bitsPerPixel, sizeof(patternHeader.bitsPerPixel));
    myfile.write((char*)&patternHeader.imageDescriptor, sizeof(patternHeader.imageDescriptor));

    for (unsigned int j = 0; j < (patternHeader.width * patternHeader.height); j++) {
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        if ((double)currentImage.pixels.at(j).red <= 127){
            red = (unsigned char)round(2*(((float)currentImage.pixels.at(j).red/255) * ((float)pattern.pixels.at(j).red/255))*255);
        } else {
            red = (unsigned char)round((1.0 - 2*((1.0 - (float)currentImage.pixels.at(j).red / 255.0) * (1.0 - (float)pattern.pixels.at(j).red / 255.0))) * 255.0);
        }
        if ((double)currentImage.pixels.at(j).green <= 127){
            green = (unsigned char)round(2*(((float)currentImage.pixels.at(j).green/255) * ((float)pattern.pixels.at(j).green/255))*255);
        } else {
            green = (unsigned char)round((1.0 - 2*((1.0 - (float)currentImage.pixels.at(j).green / 255.0) * (1.0 - (float)pattern.pixels.at(j).green / 255.0))) * 255.0);
        }
        if ((double)currentImage.pixels.at(j).blue <= 127){
            blue = (unsigned char)round(2*(((float)currentImage.pixels.at(j).blue/255) * ((float)pattern.pixels.at(j).blue/255))*255);
        } else {
            blue = (unsigned char)round((1.0 - 2*((1.0 - (float)currentImage.pixels.at(j).blue / 255.0) * (1.0 - (float)pattern.pixels.at(j).blue / 255.0))) * 255.0);
        }
//        unsigned char green = (unsigned char)round((1.0 - 2*((1.0 - (double)currentImage.pixels.at(j).green / 255.0) * (1.0 - (double)pattern.pixels.at(j).green / 255.0))) * 255.0);
//        unsigned char blue = (unsigned char)round((1.0 - ((1.0 - (double)currentImage.pixels.at(j).blue / 255.0) * (1.0 - (double)pattern.pixels.at(j).blue / 255.0))) * 255.0);
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}

void splitFile(image& currentImage, Header& headerObject){
    ofstream redFile("output/part8_r.tga", ios_base::binary);
    redFile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    redFile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    redFile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    redFile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    redFile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    redFile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    redFile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    redFile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    redFile.write((char *) &headerObject.width, sizeof(headerObject.width));
    redFile.write((char *) &headerObject.height, sizeof(headerObject.height));
    redFile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    redFile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        green = currentImage.pixels.at(j).red;
        blue = currentImage.pixels.at(j).red;
        red = currentImage.pixels.at(j).red;
        redFile.write((char *)&blue, sizeof(blue));
        redFile.write((char *)&green, sizeof(green));
        redFile.write((char *)&red, sizeof(red));
    }
    redFile.close();
    ofstream greenFile("output/part8_g.tga", ios_base::binary);
    greenFile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    greenFile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    greenFile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    greenFile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    greenFile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    greenFile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    greenFile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    greenFile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    greenFile.write((char *) &headerObject.width, sizeof(headerObject.width));
    greenFile.write((char *) &headerObject.height, sizeof(headerObject.height));
    greenFile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    greenFile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        green = currentImage.pixels.at(j).green;
        blue = currentImage.pixels.at(j).green;
        red = currentImage.pixels.at(j).green;
        greenFile.write((char *)&blue, sizeof(blue));
        greenFile.write((char *)&green, sizeof(green));
        greenFile.write((char *)&red, sizeof(red));
    }
    greenFile.close();
    ofstream blueFile("output/part8_b.tga", ios_base::binary);
    blueFile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    blueFile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    blueFile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    blueFile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    blueFile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    blueFile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    blueFile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    blueFile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    blueFile.write((char *) &headerObject.width, sizeof(headerObject.width));
    blueFile.write((char *) &headerObject.height, sizeof(headerObject.height));
    blueFile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    blueFile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int j = 0; j < (headerObject.width * headerObject.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        green = currentImage.pixels.at(j).blue;
        blue = currentImage.pixels.at(j).blue;
        red = currentImage.pixels.at(j).blue;
        blueFile.write((char *)&blue, sizeof(blue));
        blueFile.write((char *)&green, sizeof(green));
        blueFile.write((char *)&red, sizeof(red));
    }
    blueFile.close();
}

void compactFile(image& imageOne, Header& HeaderOne, image& imageTwo, Header& HeaderTwo,image& imageThree, Header& HeaderThree){
    ofstream inFile("output/part9.tga", ios_base::binary);
    inFile.write((char*)&HeaderOne.idLength, sizeof(HeaderOne.idLength));
    inFile.write((char*)&HeaderOne.colorMapType, sizeof(HeaderOne.colorMapType));
    inFile.write((char*)&HeaderOne.dataTypeCode, sizeof(HeaderOne.dataTypeCode));
    inFile.write((char *) &HeaderOne.colorMapOrigin, sizeof(HeaderOne.colorMapOrigin));
    inFile.write((char *) &HeaderOne.colorMapLength, sizeof(HeaderOne.colorMapLength));
    inFile.write((char*)&HeaderOne.colorMapDepth, sizeof(HeaderOne.colorMapDepth));
    inFile.write((char *) &HeaderOne.xOrigin, sizeof(HeaderOne.xOrigin));
    inFile.write((char *) &HeaderOne.yOrigin, sizeof(HeaderOne.yOrigin));
    inFile.write((char *) &HeaderOne.width, sizeof(HeaderOne.width));
    inFile.write((char *) &HeaderOne.height, sizeof(HeaderOne.height));
    inFile.write((char*)&HeaderOne.bitsPerPixel, sizeof(HeaderOne.bitsPerPixel));
    inFile.write((char*)&HeaderOne.imageDescriptor, sizeof(HeaderOne.imageDescriptor));
    for (unsigned int j = 0; j < (HeaderOne.width * HeaderOne.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        red = imageOne.pixels.at(j).red;
        green = imageTwo.pixels.at(j).red;
        blue = imageThree.pixels.at(j).red;
        inFile.write((char *)&blue, sizeof(blue));
        inFile.write((char *)&green, sizeof(green));
        inFile.write((char *)&red, sizeof(red));
    }
    inFile.close();
}

void rotateFile(image& currentImage, Header& headerObject){
    ofstream myfile("output/part10.tga", ios_base::binary);
    myfile.write((char*)&headerObject.idLength, sizeof(headerObject.idLength));
    myfile.write((char*)&headerObject.colorMapType, sizeof(headerObject.colorMapType));
    myfile.write((char*)&headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
    myfile.write((char *) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
    myfile.write((char *) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
    myfile.write((char*)&headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
    myfile.write((char *) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
    myfile.write((char *) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
    myfile.write((char *) &headerObject.width, sizeof(headerObject.width));
    myfile.write((char *) &headerObject.height, sizeof(headerObject.height));
    myfile.write((char*)&headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
    myfile.write((char*)&headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));
    for (unsigned int j =0; j<(headerObject.width * headerObject.height); j++) {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        green = currentImage.pixels.at(headerObject.height * headerObject.width - 1 - j).green;
        blue = currentImage.pixels.at(headerObject.height * headerObject.width - 1 - j).blue;
        red = currentImage.pixels.at(headerObject.height * headerObject.width - 1 - j).red;
//        cout << (int)red << " " << (int)green << " " <<(int)blue <<endl;
        myfile.write((char *)&blue, sizeof(blue));
        myfile.write((char *)&green, sizeof(green));
        myfile.write((char *)&red, sizeof(red));
    }
    myfile.close();
}