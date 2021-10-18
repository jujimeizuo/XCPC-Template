/*
莫比乌斯反演
g[n] = \sum_{d | n} f[d]
f[d] = \sum_{d | n} g[d] * mu[n / d]
二项式反演
g[n] = \sum{i = 1}^{n} C(n, i) * f[i]
f[n] = \sum{i = 1}^{n} C(n, i) * g[i] * (-1)^{n - i}
子集反演
f(S) = \sum_{T \belong S} g(T)
g(S) = \sum_{T \belong S} f(T) * (-1) ^ {|S| - |T|}
*/
