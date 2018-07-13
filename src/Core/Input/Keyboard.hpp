#pragma once

namespace ax
{
    enum class Keyboard : unsigned
    {
        A = 0,
        B = A + 1,
        C = B + 1,
        D = C + 1,
        E = D + 1,
        F = E + 1,
        G = F + 1,
        H = G + 1,
        I = H + 1,
        J = I + 1,
        K = J + 1,
        L = K + 1,
        M = L + 1,
        N = M + 1,
        O = N + 1,
        P = O + 1,
        Q = P + 1,
        R = Q + 1,
        S = R + 1,
        T = S + 1,
        U = T + 1,
        V = U + 1,
        W = V + 1,
        X = W + 1,
        Y = X + 1,
        Z = Y + 1,

        F1 = Z + 1,
        F2 = F1 + 1,
        F3 = F2 + 1,
        F4 = F3 + 1,
        F5 = F4 + 1,
        F6 = F5 + 1,
        F7 = F6 + 1,
        F8 = F7 + 1,
        F9 = F8 + 1,
        F10 = F9 + 1,
        F11 = F10 + 1,
        F12 = F11 + 1,

        NUM0 = F12 + 1,
        NUM1 = NUM0 + 1,
        NUM2 = NUM1 + 1,
        NUM3 = NUM2 + 1,
        NUM4 = NUM3 + 1,
        NUM5 = NUM4 + 1,
        NUM6 = NUM5 + 1,
        NUM7 = NUM6 + 1,
        NUM8 = NUM7 + 1,
        NUM9 = NUM8 + 1,

        Escape = NUM9 + 1,
        Space = Escape + 1,
        Enter = Space + 1,
        Tab = Enter + 1,
        Backspace = Tab + 1
    };
}