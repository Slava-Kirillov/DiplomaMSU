!***************************************************************
!***************************************************************
subroutine INT_2_NUM(x, rut0, m, n, k, f_0, idim, res)

    implicit none
    real*8 x(3), rut0(3, 4)
    integer m, n, idim
    integer j, i
    complex*16 res(idim), ff(idim), k
    external f_0

    real*8 p, q, p1, q1, a(3), b(3), a1(3), a2(3), a3(3), a4(3), m1(3), m2(3), rn(3), s, rc(3)

    res = 0

    do i = 1, m
        do j = 1, n
            p = (i - 1.) / m
            q = (j - 1.) / n
            p1 = (i - 0.) / m
            q1 = (j - 0.) / n

            a = q * rut0(2,:) + (1 - q) * rut0(1,:);
            b = q * rut0(3,:) + (1 - q) * rut0(4,:)

            a1 = p * b + (1 - p) * a
            a4 = p1 * b + (1 - p1) * a

            a = q1 * rut0(2,:) + (1 - q1) * rut0(1,:);
            b = q1 * rut0(3,:) + (1 - q1) * rut0(4,:);

            a2 = p * b + (1 - p) * a
            a3 = p1 * b + (1 - p1) * a

            rc = (a1 + a2 + a3 + a4) / 4.

            m1 = ((a2 + a3) - (a1 + a4)) / 2.
            m2 = ((a3 + a4) - (a1 + a2)) / 2.

            rn(1) = m1(2) * m2(3) - m1(3) * m2(2)
            rn(2) = m1(3) * m2(1) - m1(1) * m2(3)
            rn(3) = m1(1) * m2(2) - m1(2) * m2(1)

            s = dsqrt(rn(1)**2 + rn(2)**2 + rn(3)**2)

            call f_0(x, rc, k, ff)

            res = res + ff * s

        end do
    end do

    return
end