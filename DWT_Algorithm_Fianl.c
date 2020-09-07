extern const char *split_rgb_bits(IMAGE *img, FILE *fp)
{

	FILE *f1, *f2, *f3, *f4; // B, G, R, A
	unsigned char *bfB, *bfG, *bfR, *bfA;
	double *bfb, *bfg, *bfr;
	double *bfX;

	DWORD size = img->width * img->height;

	LONG s1, s2;

	//= = = = = = = = = 
	double *HH = (double *)malloc((size / 4)*sizeof(double));
	double *LL = (double *)malloc((size / 4)*sizeof(double));
	double *HL = (double *)malloc((size / 4)*sizeof(double));
	double *LH = (double *)malloc((size / 4)*sizeof(double));

	double *SHH = (double *)malloc((size / 4)*sizeof(double));
	double *SLL = (double *)malloc((size / 4)*sizeof(double));
	double *SHL = (double *)malloc((size / 4)*sizeof(double));
	double *SLH = (double *)malloc((size / 4)*sizeof(double));
	//= = = = = = = = = 
	int L = 2;

	double *h0 = (double *)malloc(L*sizeof(double));
	double *h1 = (double *)malloc(L*sizeof(double));
	double *g0 = (double *)malloc(L*sizeof(double));
	double *g1 = (double *)malloc(L*sizeof(double));
	//unsigned char h[4], g[4];
	//= = = = = = = = = 
	BYTE *ptr = img->bmpbits;
	double *dptr;

	//LONG n_width = img->width / 2;
	//LONG n_height = img->height / 2;
	//

	int b = 1, i = 0, j = 0, k = 0;
	int ori_r = img->width * img->pixdepth / 8;
	int new_r = ((DWORD)img->width * img->pixdepth + 31) / 32 * 4;
	//==========================================================//
	LONG temp;
	LONG height; LONG s_height;
	LONG width; LONG s_width;

	height = img->height;
	width = img->width;
	s_height = height / 2;
	s_width = width / 2;
	//==========================================================//

#if 1

	if (img->pixdepth == 8 || img->pixdepth == 16) {

	}
	else if (img->pixdepth == 24) {

		bfB = (unsigned char*)malloc(sizeof(unsigned char)*size);
		bfG = (unsigned char*)malloc(sizeof(unsigned char)*size);
		bfR = (unsigned char*)malloc(sizeof(unsigned char)*size);

		/*bfB = (double*)malloc(sizeof(double)*size);
		bfG = (double*)malloc(sizeof(double)*size);
		bfR = (double*)malloc(sizeof(double)*size);*/

		bfb = (double*)malloc(sizeof(double)*size);
		bfg = (double*)malloc(sizeof(double)*size);
		bfr = (double*)malloc(sizeof(double)*size);

		dptr = (double*)malloc(sizeof(double)*img->imgbytes);

		for (k = 0; k<img->imgbytes; k++) {
			*(dptr + k) = (double)*(ptr + k);
		}

		//while (i < img->imgbytes) {		// 오류
		//	bfB[j] = dptr[i++];
		//	bfG[j] = dptr[i++];
		//	bfR[j] = dptr[i++];			
		//	j++;
		//	
		//	if (i == new_r*b - (new_r - ori_r)) 
		//	{
		//		i += (new_r - ori_r);		
		//		b++;						
		//	}
		//}

		while (i < img->imgbytes) {		// 실험 중
			bfb[j] = dptr[i++];
			bfg[j] = dptr[i++];
			bfr[j] = dptr[i++];
			j++;

			if (i == new_r*b - (new_r - ori_r))
			{
				i += (new_r - ori_r);
				b++;
			}
		}

		for (i = 0; i < img->height / 2; i++) {
			for (j = 0; j < img->width; j++) {
				temp = bfb[(img->height - i - 1)*img->width + j];
				bfb[(img->height - i - 1)*img->width + j] = bfb[i*img->width + j];
				bfb[i*img->width + j] = temp;
			}
		}


     		onFilterGen(h0, h1, g0, g1, L);

		two_D_dwt(bfb, &height, &width, &L, h0, h1, LL, LH, HL, HH);

		SLL = OnScale(LL, img->height / 2, img->width / 2);
		SLH = OnScale(LH, img->height / 2, img->width / 2);
		SHL = OnScale(HL, img->height / 2, img->width / 2);
		SHH = OnScale(HH, img->height / 2, img->width / 2);

		//DH(SHH, width, height);

		for (s1 = 0; s1 < img->width / 2; s1++) {
			for (s2 = 0; s2 < img->height / 2; s2++) {
				bfB[s2*(img->width) + s1] = (char)SLL[s2*img->width / 2 + s1];
				bfB[(s2 + (img->height / 2))*(img->width) + s1] = (char)SLH[s2*img->width / 2 + s1];
				bfB[s2*(img->width) + s1 + (img->width) / 2] = (char)SHL[s2*img->width / 2 + s1];
				bfB[(s2 + (img->height / 2))*(img->width) + s1 + (img->width) / 2] = (char)SHH[s2*img->width / 2 + s1];
			}
		}

		two_D_dwt(SLL, &s_height, &s_width, &L, h0, h1, LL, LH, HL, HH);

		SLL = OnScale(LL, s_height / 2, s_width / 2);
		SLH = OnScale(LH, s_height / 2, s_width / 2);
		SHL = OnScale(HL, s_height / 2, s_width / 2);
		SHH = OnScale(HH, s_height / 2, s_width / 2);

		// DH(SLL, width, height);

		for (s1 = 0; s1 < s_width / 2; s1++) {
			for (s2 = 0; s2 < s_height / 2; s2++) {
				bfB[s2*width + s1] = (char)SLL[s2*s_width / 2 + s1];
				bfB[(s2 + (s_height / 2))*width + s1] = (char)SLH[s2*s_width / 2 + s1];
				bfB[s2*width + s1 + s_width / 2] = (char)SHL[s2*s_width / 2 + s1];
				bfB[(s2 + (s_height / 2))*width + s1 + s_width / 2] = (char)SHH[s2*s_width / 2 + s1];
			}
		}

		f1 = fopen("Blue.raw", "wb");
		fwrite(bfB, size, 1, f1);
		f2 = fopen("Green.raw", "wb");
		fwrite(bfG, size, 1, f2);
		f3 = fopen("Red.raw", "wb");
		fwrite(bfR, size, 1, f3);

		fclose(f1), fclose(f2), fclose(f3);
		free(bfB), free(bfG), free(bfR);
		free(bfb), free(bfg), free(bfr);
	}
	else if (img->pixdepth == 32) {
		size = img->width * img->height;

		bfB = (unsigned char*)malloc(sizeof(unsigned char)*size);
		bfG = (unsigned char*)malloc(sizeof(unsigned char)*size);
		bfR = (unsigned char*)malloc(sizeof(unsigned char)*size);
		bfA = (unsigned char*)malloc(sizeof(unsigned char)*size);

		while (i<img->imgbytes) {
			if (b == img->height)
				break;
			bfB[j] = ptr[i++];
			bfG[j] = ptr[i++];
			bfR[j] = ptr[i++];
			bfA[j] = ptr[i++];
			j++;
			if (i == new_r*b - (new_r - ori_r))
			{
				i += (new_r - ori_r);
				b++;
			}
		}

		for (i = 0; i < img->height / 2; i++) {  // y
			for (j = 0; j < img->width; j++) { // x				
				temp = bfA[(img->height - i - 1)*img->width + j];
				bfA[(img->height - i - 1)*img->width + j] = bfA[i*img->width + j];
				bfA[i*img->width + j] = temp;
			}
		}

		f1 = fopen("Blue.raw", "wb");
		fwrite(bfB, size, 1, f1);
		f2 = fopen("Green.raw", "wb");
		fwrite(bfG, size, 1, f2);
		f3 = fopen("Red.raw", "wb");
		fwrite(bfR, size, 1, f3);
		f4 = fopen("Alpha.raw", "wb");
		fwrite(bfA, size, 1, f4);

		fclose(f1), fclose(f2), fclose(f3), fclose(f4);
		free(bfB), free(bfG), free(bfR), free(bfA);

	}
	else
		return p_err_writeerr;

	ptr += img->imgbytes;
#else
	if (fwrite(img->bmpbits, img->imgbytes, 1, fp) != 1)
		return p_err_writeerr;
#endif
	return NULL;
}
