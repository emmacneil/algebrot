#version 130
uniform vec3 bottomLeft;
uniform float scale;
uniform int iter;

out vec4 fragColor;

void main(void)
{
    vec3 X, B;
    int i;


    B = scale * vec3(gl_FragCoord.x, gl_FragCoord.y, bottomLeft.z) + bottomLeft;
    X = B;
    for (i = 0; i < iter; i++)
    {
        float u = X.x;
        float v = X.y;
        float w = X.z;
        mat3 A = mat3(w, -u, -v,
                      v,  w, -u,
                      u,  v,  w);

        // Determinant of A
        float detA = w*w*w - v*v*v + u*u*u - 3.0f*u*v*w;
        X = A*X + B;

        // This is just a guess...
        if (detA > 8.0f)
            break;
    }

    float col = (i == iter ? 0.0 : 1.0-float(i)/float(iter));
    fragColor = vec4(col, col, col, 1.0f);
}
