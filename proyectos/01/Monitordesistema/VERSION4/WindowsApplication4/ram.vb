Public Class ram

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        Timer1.Start()

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        ProgressBar1.Value = PerformanceCounter1.NextValue
        ProgressBar2.Value = PerformanceCounter2.NextValue
        Label3.Text = ProgressBar1.Value.ToString + "%"
        Label4.Text = ProgressBar2.Value.ToString + "%"

    End Sub
End Class
