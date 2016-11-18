subroutine printMatrix(A, r, c)

    use iso_c_binding

    integer(c_int) :: r, c
    real(c_double) :: A(r,c)
    integer(c_int) :: i, j

    do i=1, r
        write(*,*) (A(i,j), j=1,c)
    end do

end subroutine printMatrix

subroutine multiply(a, b, c, a_rows, a_cols, b_rows, b_cols) bind(C, NAME="multiply")

    use iso_c_binding

    integer(c_int), value :: a_rows, a_cols, b_rows, b_cols
    real(c_double) :: a(a_rows, a_cols)
    real(c_double) :: b(b_rows, b_cols)
    real(c_double) :: c(a_rows, b_cols)

    print*, 'a (from Fortran) = '
    call printMatrix(A, a_rows, a_cols)

    c = matmul(a, b)
    
end subroutine multiply
