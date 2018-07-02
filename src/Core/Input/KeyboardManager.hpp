#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>

#include <unordered_map>

namespace ax
{
    enum Keyboard : unsigned
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
        NUM0 = Z + 1,
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

    class AXION_CORE_API KeyboardManager
    {
    public:
        virtual bool isKeyPressed(Keyboard key) const noexcept = 0;
        virtual bool isKeyReleased(Keyboard key) const noexcept = 0;
        
        bool isKeyPressed(std::string name) const noexcept;
        bool isKeyReleased(std::string name) const noexcept;

        void addInput(std::string name, Keyboard key) noexcept;
        void removeInput(std::string name) noexcept;
        Keyboard getInput(std::string name) const noexcept;
        void setInput(std::string name, Keyboard key) noexcept;

    private:
        std::unordered_map<std::string, Keyboard> m_inputs;
    };
}