Public Class Form1

    Private Sub ListBox1_SelectedIndexChanged(sender As Object, e As EventArgs) Handles filesListBox.SelectedIndexChanged

    End Sub

    Private Sub browseButton1_Click(sender As Object, e As EventArgs) Handles browseButton1.Click
        If FolderBrowserDialog1.ShowDialog() = DialogResult.OK Then
            ' List files in the folder.
            ListFiles(FolderBrowserDialog1.SelectedPath)
        End If
    End Sub
    Private Sub ListFiles(ByVal folderPath As String)
        filesListBox.Items.Clear()

        Dim fileNames = My.Computer.FileSystem.GetFiles(
            folderPath, FileIO.SearchOption.SearchTopLevelOnly, "*.txt")

        For Each fileName As String In fileNames
            filesListBox.Items.Add(fileName)
        Next
    End Sub

    Private Sub examineButton2_Click(sender As Object, e As EventArgs) Handles examineButton2.Click
        If filesListBox.SelectedItem Is Nothing Then
            MessageBox.Show("Seleccione un archivo.")
            Exit Sub
        End If

        ' Obtain the file path from the list box selection.
        Dim filePath = filesListBox.SelectedItem.ToString

        ' Verify that the file was not removed since the
        ' Browse button was clicked.
        If My.Computer.FileSystem.FileExists(filePath) = False Then
            MessageBox.Show("File Not Found: " & filePath)
            Exit Sub
        End If

        ' Obtain file information in a string.
        Dim fileInfoText As String = GetTextForOutput(filePath)

        ' Show the file information.
        MessageBox.Show(fileInfoText)

        If saveCheckBox.Checked = True Then
            ' Place the log file in the same folder as the examined file.
            Dim logFolder As String = My.Computer.FileSystem.GetFileInfo(filePath).DirectoryName
            Dim logFilePath = My.Computer.FileSystem.CombinePath(logFolder, "registro.txt")

            Dim logText As String = "Fecha de creacion: " & Date.Now.ToString &
                vbCrLf & fileInfoText & vbCrLf & vbCrLf

            ' Append text to the log file.
            My.Computer.FileSystem.WriteAllText(logFilePath, logText, append:=True)
        End If
    End Sub

    Private Function GetTextForOutput(ByVal filePath As String) As String
        ' Verify that the file exists.
        If My.Computer.FileSystem.FileExists(filePath) = False Then
            Throw New Exception("File Not Found: " & filePath)
        End If

        ' Create a new StringBuilder, which is used
        ' to efficiently build strings.
        Dim sb As New System.Text.StringBuilder()

        ' Obtain file information.
        Dim thisFile As System.IO.FileInfo = My.Computer.FileSystem.GetFileInfo(filePath)

        ' Add file attributes.
        sb.Append("Archivo: " & thisFile.FullName)
        sb.Append(vbCrLf)
        sb.Append("Modificacion: " & thisFile.LastWriteTime.ToString)
        sb.Append(vbCrLf)
        sb.Append("Tamaño: " & thisFile.Length.ToString & " bytes")
        sb.Append(vbCrLf)

        ' Open the text file.
        Dim sr As System.IO.StreamReader =
            My.Computer.FileSystem.OpenTextFileReader(filePath)

        ' Add the first line from the file.
        If sr.Peek() >= 0 Then
            sb.Append("Primera linea " & sr.ReadLine())
        End If
        sr.Close()

        Return sb.ToString
    End Function

    Private Sub saveCheckBox_CheckedChanged(sender As Object, e As EventArgs) Handles saveCheckBox.CheckedChanged

    End Sub
End Class
