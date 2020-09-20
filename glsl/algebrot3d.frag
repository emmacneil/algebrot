#version 130
uniform vec3 bottomLeft;
uniform vec3 modulus;
uniform float scale;
uniform int iter;

out vec4 fragColor;

void main(void)
{
    float a = modulus.x, b = modulus.y; // Coefficients of t^2 + at + b = 0, from the modulus polynomial
    vec3 X, B;
    int i;

    mat3 T = mat3(0, 1, 0, 0, 0, 1, -modulus.z, -modulus.y, -modulus.x);
    mat3 I = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    B = scale * (gl_FragCoord.x, gl_FragCoord.y, 0) + bottomLeft;
    X = B;
    for (i = 0; i < iter; i++)
    {
        float x = X.x, y = X.y; // Coefficients of yt + x, from the given point
        mat3 A = (X.z*T + X.y*I)*T + X.x*I;

        // Determinant of A
        float detA = A[0][0]*A[1][1]*A[2][2]
                   + A[0][1]*A[1][2]*A[2][0]
                   + A[0][2]*A[1][0]*A[2][1]
                   - A[0][2]*A[1][1]*A[2][0]
                   - A[0][1]*A[1][0]*A[2][2]
                   - A[0][0]*A[1][2]*A[2][1];
        X = A*X + B;

        // This is just a guess...
        if (detA > 8.0f)
            break;
    }

    float col = (i == iter ? 0.0 : 1.0-float(i)/float(iter));
    fragColor = vec4(col, col, col, 1.0f);
}
