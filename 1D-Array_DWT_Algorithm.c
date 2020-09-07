extern const void *dwt(double *Vin, int *M, int *L, double *h0, double *h1,
	double *Wout, double *Vout) // 1차원 dwt
{
	int n, t, u;

	for (t = 0; t < *M / 2; t++) {
		u = 2 * t + 1;
		Wout[t] = h0[0] * Vin[u];
		Vout[t] = h1[0] * Vin[u];
		for (n = 1; n < *L; n++) {	// L : FilterTap
			u -= 1;
			if (u < 0) u = *M - 1;
			Wout[t] += h0[n] * Vin[u];
			Vout[t] += h1[n] * Vin[u];	// convolution 
		}
	}
}
