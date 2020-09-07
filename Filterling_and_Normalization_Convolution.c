double * OnScale(double *Target, int height, int width)
{
	//정규화 함수 : 필터링된 값을 0~255 사이의 값으로 정규화
	int i, j;
	double min, max;
	double *temp;

	temp = (double*)malloc(sizeof(double)*height*width);

	min = max = Target[0];

	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			if (Target[j*width + i] <= min) {
				min = Target[j*width + i];
			}

			if (Target[j*width + i] >= max) {
				max = Target[j*width + i];
			}
		}
	}

	max = max - min;

	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			temp[j*width + i] = (Target[j*width + i] - min) * (255. / max);
		}
	}
	return temp;
}

void *onFilterGen(double *h0, double *h1, double *g0, double *g1, int FilterTap)
{
	int i;
	switch (FilterTap)
	{
	case 2:
		h0[0] = 0.70710678118655; // L=2일 경우
		h0[1] = 0.70710678118655;
		break;
	case 4:
		h0[0] = -0.12940952255092;
		h0[1] = 0.22414386804186;
		h0[2] = 0.83651630373747;
		h0[3] = 0.48296291314469;
		break;
	default:
		printf("Wrong Filter");
		return NULL;
	}

	for (i = 0; i<FilterTap; i++) {
		h1[i] = pow(-1.0, i + 1) * h0[FilterTap - i - 1];
	}

	for (i = 0; i<FilterTap; i++) {
		g0[i] = h0[FilterTap - i - 1];
	}

	for (i = 0; i<FilterTap; i++) {
		g1[i] = pow(-1.0, i) * h0[i];
	}
}
