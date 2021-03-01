#pragma once

struct Vec3 {
    float x, y, z;

    Vec3 operator+(Vec3 d) //vektoreiden plussaus
    {
        return { x + d.x, y + d.y, z + d.z };
    }
    Vec3 operator-(Vec3 d) //vektoreiden miinustus
    {
        return { x - d.x, y - d.y, z - d.z };
    }
    Vec3 operator*(float d) //vektoreiden kertominen
    {
        return { x * d, y * d, z * d };
    }

    void Normalize() //y on vaakataso x pystytaso csgo:ssa
    {
        while (y < -180) {
            y += 360;
        }
        while (y > 180) {
            y -= 360;
        }
        if (x > 89) {
            x = 89;
        }
        if (x < -89) {
            x = -89;
        }
    }

};