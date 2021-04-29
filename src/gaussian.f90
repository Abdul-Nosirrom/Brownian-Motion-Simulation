SUBROUTINE gaussian(val) 

  ! Adapted From Source: https://jblevins.org/mirror/amiller/random.f90
  IMPLICIT NONE

  REAL :: val
  REAL :: s=0.449871, t=-0.386595, a=0.19600, b=0.25472, r1=0.27597, r2=0.27846, u,v,x,y,q

  DO 
    CALL RANDOM_NUMBER(u)
    CALL RANDOM_NUMBER(v)
    v = 1.7156 * (v-0.5)

    x = u - s
    y = ABS(v) - t
    q = x**2 + y*(a*y-b*x)

    IF (q<r1) EXIT
    IF (q>r2) CYCLE
    IF (v**2 < -4.0*LOG(u)*u**2) EXIT
  END DO

  val = v/u
  

END SUBROUTINE gaussian

