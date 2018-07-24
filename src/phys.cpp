//
// Created by Ronin748 on 21.12.2015.
//

#include <phys.h>
#include <util/randomRange.h>

void Phys::tick()
{
        if (!nnv(forces)) // NULL precaution
                forces = glm::vec3(0.0f);
        if (!nnv(torx))
                torx = glm::vec3(0.0f);
        if (!nnv(v)) // NULL precaution
                v = glm::vec3(0.0f);
        if (!nnv(rot_v))
                rot_v = glm::vec3(0.0f);
        if (!nn(qrot))
                qrot = glm::quat(rot);

        forcesold = forces;
        torxold = torx;
        a = (forces / (m));
        v += a;
        pos += v;

        // nulls can happen here
        float rDiff = (float) glm::length(rpos - pos) + 0.01f;

        // null == true always
        if (rDiff > 1.0f)
                rDiff = 1.0f;

        rpos = rpos * (1.0f - rDiff) + rDiff * pos;

        float rrDiff = (float) glm::length(rrot - rot) + 0.01f;

        // null == true always
        if (rrDiff > 1.0f)
                rrDiff = 1.0f;

        rrot = rrot * (1.0f - rrDiff) + rrDiff * rot;
        qrrot = qrrot * (1.0f - rrDiff) + rrDiff * qrot;

        rot_a = torx / I;
        rot_v += rot_a;
        rot += rot_v;

        sv = sv*0.95f+v*0.05f;
        srot_v = srot_v*0.95f+rot_v*0.05f;

        glm::quat qr = glm::quat(rot_v);
        qrot = qr * qrot;

        p = m * v;

        forces = glm::vec3(0.0f);
        torx = glm::vec3(0.0f);
}

void Phys::update()
{
        if (!isStatic) tick();
        else {
                rpos = pos;
                qrot = glm::quat(rot);
                qrrot = qrot;
        }
}

void Phys::applyForce(glm::vec3 force)
{
        forces += force;
        tick();
}

void Phys::setRot(glm::vec3 r)
{
        rot = r;
        rrot = rot;

        qrot = glm::quat(rot);
        qrrot = qrot;
}

glm::mat4 makeRotationDir(glm::vec3 direction, glm::vec3 up)
{
        glm::mat4 rotm = glm::mat4(1.0f);
        glm::vec3 xaxis = glm::cross(up, direction);
        xaxis = normalize(xaxis);

        glm::vec3 yaxis = glm::cross(direction, xaxis);
        yaxis = normalize(yaxis);

        rotm[0][0] = xaxis.x;
        rotm[1][0] = yaxis.x;
        rotm[2][0] = direction.x;

        rotm[0][1] = xaxis.y;
        rotm[1][1] = yaxis.y;
        rotm[2][1] = direction.y;

        rotm[0][2] = xaxis.z;
        rotm[1][2] = yaxis.z;
        rotm[2][2] = direction.z;

        return rotm;
}

glm::mat4 gimbalRotate(glm::mat4 m, glm::vec3 r, glm::vec3 r_o = glm::vec3(0.0f))
{
        glm::quat qr = glm::quat(r);

        qr = qr * glm::quat(r_o);

        m = m * glm::toMat4(qr);

        return m;
}

glm::mat4 Phys::getMatrix()
{
        glm::mat4 objMatrix = glm::mat4(1.0f);

        objMatrix = glm::translate(objMatrix, pos + v);

        objMatrix *= glm::toMat4(qrot);
        //objMatrix *= glm::axisAngleMatrix(rot, glm::length(rot));

        objMatrix = glm::scale(objMatrix, s);

        objMatrix = glm::translate(objMatrix, rot_offs);

        return objMatrix;
}

glm::mat4 Phys::getRMatrix()
{
        glm::mat4 objMatrix = glm::mat4(1.0f);

        objMatrix = glm::translate(objMatrix, rpos);

        objMatrix *= glm::toMat4(qrrot);
        //objMatrix *= glm::axisAngleMatrix(rot, glm::length(rot));

        objMatrix = glm::scale(objMatrix, s);

        objMatrix = glm::translate(objMatrix, rot_offs);

        return objMatrix;
}
