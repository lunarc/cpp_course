! Solves a tridiagonal linear system with the Thomas algorithm.
!
!   a(i) x(i-1) + b(i) x(i) + c(i) x(i+1) = d(i),   i = 1..n
!
! bind(C) gives the routine a predictable, C-compatible name and
! calling convention, so it can be called directly from C++.

module tridiag_mod
    use, intrinsic :: iso_c_binding, only: c_int, c_double
    implicit none

contains

    subroutine solve_tridiagonal(n, a, b, c, d, x) bind(C, name="solve_tridiagonal")
        integer(c_int), value, intent(in) :: n
        real(c_double), intent(in)  :: a(n), b(n), c(n), d(n)
        real(c_double), intent(out) :: x(n)

        real(c_double) :: cp(n), dp(n), m
        integer :: i

        cp(1) = c(1) / b(1)
        dp(1) = d(1) / b(1)

        do i = 2, n
            m = b(i) - a(i) * cp(i - 1)
            cp(i) = c(i) / m
            dp(i) = (d(i) - a(i) * dp(i - 1)) / m
        end do

        x(n) = dp(n)
        do i = n - 1, 1, -1
            x(i) = dp(i) - cp(i) * x(i + 1)
        end do
    end subroutine solve_tridiagonal

end module tridiag_mod
