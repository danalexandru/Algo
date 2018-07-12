Attribute VB_Name = "Module1"

Public Sub RezolvEcuatieGradI( _
            ByVal a As Single, _
            ByVal b As Single, _
            ByRef sol As Single, _
            ByRef cod As Byte)
    '
    ' rezolva a*x+b=0
    ' cod = 0, solutie determinata
    ' cod = 1, ecuatie nedeterminata
    ' cod = 2, ecuatie imposibila
    '
    If a = 0 Then
        If b = 0 Then
            cod = 1
        Else
            cod = 2
        End If
    Else
        cod = 0
        sol = -b / a
    End If
End Sub


Public Sub ApelEcuatieGradI()
    Dim sngA As Single, sngB As Single, sngSolutie As Single
    Dim byteCod As Byte
    '
    ' se citesc valorile coeficientilor a si b
    '
    sngA = InputBox("Coeficientul a", "Coeficientii ecuatiei a*x+b=0")
    sngB = InputBox("Coeficientul b", "Coeficientii ecuatiei a*x+b=0")
    '
    ' se apeleaze procedura de rezolvare a ecuatiei
    '
    RezolvEcuatieGradI a:=sngA, b:=sngB, sol:=sngSolutie, cod:=byteCod
    '
    ' se afiseaza solutia
    '
    Select Case byteCod
        Case 0
            MsgBox sngSolutie, vbOKOnly, "Ecuatie determinata"
        Case 1
            MsgBox "", vbOKOnly, "Ecuatie nedeterminata"
        Case 2
            MsgBox "", vbOKOnly, "Ecuatie imposibila"
    End Select
End Sub
