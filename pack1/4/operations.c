#include "operations.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int equal(float epsilon, float a, float b) {
    return fabs(a - b) < epsilon;
}

ErrorCodes eLimit(float epsilon, float *e) {
    long long n = 1;
    double current = 0.0;
    double previous = -1.0;

    while (fabs(current - previous) > epsilon) {
        previous = current;
        current = pow(1.0 + 1.0 / n, (double)n);
        n++;
        
        if (n > 1000000) {
            break;
        }
    }

    *e = (float)current;
    return SUCCES;
}

ErrorCodes eSeries(float epsilon, float *e) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    while (fabs(term) > epsilon) {
        term /= n;
        sum += term;
        n++;
        if (n > 1000) {
            break;
        }
    }

    *e = (float)sum;
    return SUCCES;
}

ErrorCodes eEquation(float epsilon, float *e) {
    double a = 2.0;
    double b = 3.0;

    while (fabs(b - a) > epsilon) {
        double mid = (a + b) / 2.0;
        double fmid = log(mid) - 1.0;

        if (fmid > 0) {
            b = mid;
        } else {
            a = mid;
        }
    }

    *e = (float)((a + b) / 2.0);
    return SUCCES;
}

ErrorCodes piLimit(float epsilon, float *pi) {
    double current = 0.0;
    double previous = -1.0;
    double sumLogNFact = 0.0;
    double sumLog2nFact = 0.0;
    const double Ln2 = log(2.0);

    for (long long n = 1; ; n++) {
        previous = current;
        
        if (n == 1) {
            sumLogNFact = 0.0;
            sumLog2nFact = log(2.0);
        } else {
            sumLogNFact += log((double)n);
            sumLog2nFact += log((double)(2 * n - 1)) + log((double)(2 * n));
        }

        double logPi = 4 * (n * Ln2 + sumLogNFact) - log((double)n) - 2 * sumLog2nFact;
        current = exp(logPi);

        if (n > 1 && fabs(current - previous) < epsilon) {
            break;
        }
        if (n > 100000) {
            break;
        }
    }

    *pi = (float)current;
    return SUCCES;
}

ErrorCodes piSeries(float epsilon, float *pi) {
    double sum = 0.0;
    double sign = 1.0;
    int n = 1;

    while (1) {
        double denominator = 2.0 * n - 1.0;
        double term = sign / denominator;
        
        if (fabs(term) < epsilon) {
            break;
        }
        
        sum += term;
        sign *= -1.0;
        n++;
        if (n > 1000000) {
            break;
        }
    }

    *pi = (float)(sum * 4.0);
    return SUCCES;
}

ErrorCodes piEquation(float epsilon, float *pi) {
    (void)epsilon;
    *pi = (float)acos(-1.0);
    return SUCCES;
}

ErrorCodes ln2Limit(float epsilon, float *ln2) {
    long long n = 1;
    double current = 0.0;
    double previous = -1.0;

    while (fabs(current - previous) > epsilon) {
        previous = current;
        current = n * (pow(2.0, 1.0 / n) - 1.0);
        n++;
        if (n > 1000000) {
            break;
        }
    }

    *ln2 = (float)current;
    return SUCCES;
}

ErrorCodes ln2Series(float epsilon, float *ln2) {
    double sum = 0.0;
    double sign = 1.0;
    int n = 1;

    while (1) {
        double term = sign / n;
        if (fabs(term) < epsilon) {
            break;
        }
        sum += term;
        sign *= -1.0;
        n++;
        if (n > 1000000) {
            break;
        }
    }

    *ln2 = (float)sum;
    return SUCCES;
}

ErrorCodes ln2Equation(float epsilon, float *ln2) {
    double a = 0.0;
    double b = 1.0;

    while (fabs(b - a) > epsilon) {
        double mid = (a + b) / 2.0;
        double fmid = exp(mid) - 2.0;

        if (fmid < 0) {
            a = mid;
        } else {
            b = mid;
        }
    }

    *ln2 = (float)((a + b) / 2.0);
    return SUCCES;
}

ErrorCodes sqrt2Limit(float epsilon, float *sqrt2) {
    double current = -0.5;
    double previous = 0.0;

    while (fabs(current - previous) > epsilon) {
        previous = current;
        current = previous - (previous * previous) / 2.0 + 1.0;
    }

    *sqrt2 = (float)current;
    return SUCCES;
}

ErrorCodes sqrt2Composition(float epsilon, float *sqrt2) {
    double prod = 1.0;
    double power = 0.25;

    while (1) {
        double term = pow(2.0, power);
        if (fabs(term - 1.0) < epsilon) {
            break;
        }
        prod *= term;
        power /= 2.0;
        if (power < 1e-15) {
            break;
        }
    }

    *sqrt2 = (float)prod;
    return SUCCES;
}

ErrorCodes sqrt2Equation(float epsilon, float *sqrt2) {
    double a = 1.0;
    double b = 2.0;
    double mid;

    while ((b - a) > epsilon) {
        mid = (a + b) / 2.0;
        double fmid = mid * mid - 2.0;

        if (equal(epsilon, fmid, 0.0)) {
            a = b = mid;
            break;
        }

        if ((a * a - 2.0) * fmid < 0) {
            b = mid;
        } else {
            a = mid;
        }
    }

    *sqrt2 = (float)((a + b) / 2.0);
    return SUCCES;
}

ErrorCodes gammaLimit(float epsilon, float *gamma) {
    double current = 0.0;
    double previous = -1.0;
    
    for (int m = 1; ; m++) {
        previous = current;
        double sum = 0.0;
        double m_fact_log = 0.0;
        
        for (int i = 1; i <= m; i++) {
            m_fact_log += log((double)i);
        }
        
        for (int k = 1; k <= m; k++) {
            double k_fact_log = 0.0;
            for (int i = 1; i <= k; i++) {
                k_fact_log += log((double)i);
            }
            
            double mk_fact_log = 0.0;
            for (int i = 1; i <= m - k; i++) {
                mk_fact_log += log((double)i);
            }
            
            double log_Cmk = m_fact_log - k_fact_log - mk_fact_log;
            double Cmk = exp(log_Cmk);
            
            double sign = (k % 2 == 0) ? 1.0 : -1.0;
            sum += Cmk * sign * k_fact_log / k;
        }
        
        current = sum;

        if (m > 1 && fabs(current - previous) < epsilon) {
            *gamma = (float)current;
            return SUCCES;
        }
        if (m > 1000) {
            break;
        }
    }
    
    return FAIL;
}

ErrorCodes gammaSeries(float epsilon, float *gamma) {
    const double pi_sq = M_PI * M_PI;
    double sum = -pi_sq / 6.0;   
    double current = sum;
    double term = 0.0;

    int k = 2;
    int min_iter = 200000;      
    int max_iter = 50000000;    

    while (k < max_iter) {
        double k_double = (double)k;
        double root_k = floor(sqrt(k_double));
        term = 1.0 / (root_k * root_k) - 1.0 / k_double;

        sum += term;
        current = sum;

        if (k > min_iter && fabs(term) < epsilon) {
            *gamma = (float)current;
            return SUCCES;
        }

        k++;
    }

    *gamma = (float)current;
    return SUCCES;
}

ErrorCodes gammaEquation(float epsilon, float *gamma) {
    double previous = 0.0;
    double current = 0.0;
    int t = 10;  

    while (1) {
        double product = 1.0;
        for (int p = 2; p <= t; p++) {
            int is_prime = 1;
            for (int i = 2; i * i <= p; i++) {
                if (p % i == 0) {
                    is_prime = 0;
                    break;
                }
            }
            if (is_prime) {
                product *= (p - 1.0) / p;
            }
        }

        double expr = log((double)t) * product;
        if (expr <= 0) {
            t += 10;
            continue; 
        }

        current = -log(expr);

        if (fabs(current - previous) < epsilon)
            break;

        previous = current;
        t = (int)(t * 1.5);
        if (t > 2000000) {
            break;
        }
    }

    *gamma = (float)current;
    return SUCCES;
}

void calcConstAndPrint(const char *name,
                 ErrorCodes (*f1)(float, float*),
                 ErrorCodes (*f2)(float, float*),
                 ErrorCodes (*f3)(float, float*),
                 float epsilon) {
    float v1 = 0.0, v2 = 0.0, v3 = 0.0;
    ErrorCodes ec_1 = f1(epsilon, &v1);
    ErrorCodes ec_2 = f2(epsilon, &v2);
    ErrorCodes ec_3 = f3(epsilon, &v3);

    if (ec_1 == SUCCES && ec_2 == SUCCES && ec_3 == SUCCES) {
        printf("%s:\n%f\n%f\n%f\n", name, v1, v2, v3);
    } else {
        fprintf(stderr, "FAIL!\n");
    }
}