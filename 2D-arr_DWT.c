extern const void *two_D_dwt(double *X, int *M, int *N, int *L, double *h, double *g,
	double *LL, double *LH, double *HL, double *HH)
{
	int i, j, k;
	//unsigned char *data, *Wout, *Vout, *Low, *High;
	double *data, *Wout, *Vout, *Low, *High;

	FILE *f;

	/*
	*  Perform one-dimensional DWT on columns (length M).
	*/

	Wout = (double *)malloc((*M) * sizeof(double));
	Vout = (double *)malloc((*M) * sizeof(double));
	//Wout = (unsigned char *)malloc((*M) * sizeof(unsigned char));
	//Vout = (unsigned char *)malloc((*M) * sizeof(unsigned char));

	/*
	*  Create temporary "matrices" to store DWT of columns.
	*/
	Low = (double *)malloc((*N*(*M / 2)) * sizeof(double));
	High = (double *)malloc((*N*(*M / 2)) * sizeof(double));
	//Low = (unsigned char *)malloc((*N*(*M / 2)) * sizeof(unsigned char));
	//High = (unsigned char *)malloc((*N*(*M / 2)) * sizeof(unsigned char));

	for (i = 0; i < *N; i++) {
		/*
		*  Must take column from X and place into vector for DWT.
		*/
		data = (double *)malloc((*M) * sizeof(double));
		//data = (unsigned char *)malloc((*M) * sizeof(unsigned char));
		for (j = 0; j < *M; j++) {
			data[j] = X[i*(*M) + j];	// 이 때의 data는 column 입력을 위한 배열
										/* printf("X[%d][%d] = %f\n", i, j, X[i*(*M)+j]); */
		}
		/*
		*  Perform DWT and read into temporary matrices.
		*/
		//dwt(&data, &M, &L, &h, &g, &Wout, &Vout);


		dwt(data, M, L, h, g, Wout, Vout);

		//f = fopen("Wout.raw", "wb");
		//fwrite(Wout, sizeof(char), *M, f);
		//fclose(f);

		for (k = 0; k < (int)*M / 2; k++) {
			High[i*((*M) / 2) + k] = Vout[k];
			Low[i*((*M) / 2) + k] = Wout[k];
			/* printf("Low[%d][%d] = %f\n", i, k, Low[i*(*M/2)+k]);
			printf("High[%d][%d] = %f\n", i, k, High[i*(*M/2)+k]); */
		}
		free(data);
	}

	free(Wout);
	free(Vout);
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================
	//==================================================================================



	/*
	*  Perform one-dimensional DWT on rows (length N).
	*/

	Wout = (double *)malloc((*N) * sizeof(double));
	Vout = (double *)malloc((*N) * sizeof(double));
	//Wout = (unsigned char *)malloc((*N) * sizeof(unsigned char));
	//Vout = (unsigned char *)malloc((*N) * sizeof(unsigned char));



	for (i = 0; i < (int)*M / 2; i++) {
		/*
		*  Must take row from "Low" and place into vector for DWT.
		*/
		data = (double *)malloc((*N) * sizeof(double));
		//data = (unsigned char *)malloc((*N) * sizeof(unsigned char));
		for (j = 0; j < *N; j++) {
			data[j] = Low[i + j*(*M / 2)];
			/* printf("Low[%d][%d] = %f\n", i, j, Low[i+j*(*M/2)]); */
		}
		/*
		*  Perform DWT and read into final "Low" matrices.
		*/
		dwt(data, N, L, h, g, Wout, Vout);
		//dwt(&data, &N, &L, &h, &g, &Wout, &Vout);
		for (k = 0; k < (int)*N / 2; k++) {
			HL[i + k*(*N / 2)] = Vout[k];
			LL[i + k*(*N / 2)] = Wout[k];
			/* printf("LL[%d][%d] = %f\n", i, k, LL[i+k*(*N/2)]);
			printf("LH[%d][%d] = %f\n", i, k, HL[i+k*(*N/2)]); */
		}
		free(data);

		//==================================================================================
		//==================================================================================
		//==================================================================================
		//==================================================================================

		/*
		*  Must take row from "High" and place into vector for DWT.
		*/
		data = (double *)malloc((*N) * sizeof(double));
		//data = (unsigned char *)malloc((*N) * sizeof(unsigned char));
		for (j = 0; j < *N; j++) {
			data[j] = High[i + j*(*M / 2)];
			/* printf("High[%d][%d] = %f\n", j, i, High[i+j*(*M/2)]); */
		}
		/*
		*  Perform DWT and read into final "High" matrices.
		*/
		dwt(data, N, L, h, g, Wout, Vout);
		//dwt(&data, &N, &L, &h, &g, &Wout, &Vout);
		for (k = 0; k < (int)*N / 2; k++) {
			HH[i + k*(*N / 2)] = Vout[k];
			LH[i + k*(*N / 2)] = Wout[k];
			/* printf("HL[%d][%d] = %f\n", i, k, LH[i+k*(*N/2)]);
			printf("HH[%d][%d] = %f\n", i, k, HH[i+k*(*N/2)]); */
		}
		free(data);
	}

	free(Wout);
	free(Vout);
	free(Low);
	free(High);
}
