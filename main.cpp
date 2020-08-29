/*
 * Copyright (c) 2013, Marc Lebrun <marc.lebrun.ik@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can use, modify and/or
 * redistribute it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later
 * version. You should have received a copy of this license along
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <string>
#include <sstream>
#include "Utilities/Utilities.h"
#include "NlBayes/NlBayes.h"
#include "Utilities/LibImages.h"
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>
using namespace std;



/**
 * @file   main.cpp
 * @brief  Main executable file
 *
 *
 *
 * @author MARC LEBRUN  <marc.lebrun.ik@gmail.com>
 **/

int main(int argc, char **argv)
{
    //! Check if there is the right call for the algorithm
	if (argc < 13) {
		cout << "usage: NL_Bayes image sigma noisy denoised basic difference \
		bias basic_bias diff_bias useArea1 useArea2 computeBias" << endl;
		return EXIT_FAILURE;
	}

    //! Variables initialization
	const float sigma   = atof(argv[2]);
	const bool doBias   = (bool) atof(argv[12]);
	const bool useArea1 = (bool) atof(argv[10]);
	const bool useArea2 = (bool) atof(argv[11]);
	const bool verbose  = true;


	//! Declarations
	vector<float> im, imNoisy, im_aniso,imBasic, imFinal, imDiff,img2;
	vector<float> imBias, imBasicBias, imDiffBias;
	ImageSize imSize,imSize_sym;

    //! Load image
	if(loadImage(argv[1], img2, imSize, verbose) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
	}

		if(loadImage("8.png", im, imSize, verbose) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
	}


	//addNoise(im, imNoisy, sigma, verbose);

	//if (saveImage("imNoisy.png", imNoisy, imSize, 0.f, 255.f) != EXIT_SUCCESS) {
	///	return EXIT_FAILURE;
//	}
	//im_aniso=im;
	// anisotropicSmoothing
	/*for(unsigned i=0;i<150;i++)
	if(anisotropicSmoothing(imNoisy,imSize)!= EXIT_SUCCESS){
		return EXIT_FAILURE;
	}*/

	//! Denoising
    if (verbose) {
        cout << endl << "Applying NL-Bayes to the noisy image :" << endl;
    }
    if (runNlBayes(img2, imBasic, imFinal, imSize, useArea1, useArea2, sigma, verbose)
        != EXIT_SUCCESS) {
        return EXIT_FAILURE;
		}



	//! Compute PSNR and RMSE
    float psnr, rmse, psnrBasic, rmseBasic;
    computePsnr(im, imBasic, psnrBasic, rmseBasic, "imBasic", verbose);
    computePsnr(im, imFinal, psnr, rmse, "imFinal", verbose);
    float psnrBias, psnrBiasBasic, rmseBias, rmseBiasBasic;

    //! writing measures
    writingMeasures("measures.txt", sigma, psnrBasic, rmseBasic, true, "_basic");
    writingMeasures("measures.txt", sigma, psnr, rmse, false, "      ");

    //! Compute Difference
	if (computeDiff(im, imFinal, imDiff, sigma, 0.f, 255.f, verbose) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
	}

	if (saveImage("im_an.png", imFinal, imSize, 0.f, 255.f) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}



	return 0;
	// normalize image  
	/*if(normalize_image(im,im_normalize_image,imSize,0,1)!= EXIT_SUCCESS){
		return EXIT_FAILURE;
	}*/
	/*if(gradientX(im,gradx,imSize,1)!= EXIT_SUCCESS){
		return EXIT_FAILURE;
	}*/



	//orientationImage
	/*if(ridgeOrient(im_normalize_image, gradientsigma, blocksigma,
										 orientsmoothsigma)!= EXIT_SUCCESS){
		return EXIT_FAILURE;
	}*/

	//calcul gradien 

    //! save noisy, denoised and differences images
	if (verbose) {
	    cout << "Save images...";
	}

	if (saveImage("8_sym.png", imDiff, imSize_sym, 0.f, 255.f) != EXIT_SUCCESS) {
		return EXIT_FAILURE;
	}
    if (verbose) {
        cout << "done." << endl;
    }


	#define smooth_kernel_size 7
	#define sigma 1.0
	#define K  1

	
	








	return EXIT_SUCCESS;
}
