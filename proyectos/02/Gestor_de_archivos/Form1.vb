Imports System.IO
Imports System.IO.Compression
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
            folderPath, FileIO.SearchOption.SearchTopLevelOnly, "*.*")

        For Each fileName As String In fileNames
            filesListBox.Items.Add(fileName)
        Next
    End Sub

    Private Sub examineButton2_Click(sender As Object, e As EventArgs) Handles examineButton2.Click
        If filesListBox.SelectedItem Is Nothing Then
            MessageBox.Show("Seleccione un archivo.")
            Exit Sub
        End If


        Dim filePath = filesListBox.SelectedItem.ToString

        If My.Computer.FileSystem.FileExists(filePath) = False Then
            MessageBox.Show("File Not Found: " & filePath)
            Exit Sub
        End If

        Dim fileInfoText As String = GetTextForOutput(filePath)


        MessageBox.Show(fileInfoText)

        If saveCheckBox.Checked = True Then

            Dim logFolder As String = My.Computer.FileSystem.GetFileInfo(filePath).DirectoryName
            Dim logFilePath = My.Computer.FileSystem.CombinePath(logFolder, "registro.txt")

            Dim logText As String = "Fecha de creacion: " & Date.Now.ToString &
                vbCrLf & fileInfoText & vbCrLf & vbCrLf


            My.Computer.FileSystem.WriteAllText(logFilePath, logText, append:=True)
        End If
    End Sub

    Private Function GetTextForOutput(ByVal filePath As String) As String

        If My.Computer.FileSystem.FileExists(filePath) = False Then
            Throw New Exception("File Not Found: " & filePath)
        End If

      
        Dim sb As New System.Text.StringBuilder()


        Dim thisFile As System.IO.FileInfo = My.Computer.FileSystem.GetFileInfo(filePath)

        sb.Append("Archivo: " & thisFile.FullName)
        sb.Append(vbCrLf)
        sb.Append("Modificacion: " & thisFile.LastWriteTime.ToString)
        sb.Append(vbCrLf)
        sb.Append("Tamaño: " & thisFile.Length.ToString & " bytes")
        sb.Append(vbCrLf)


        Dim sr As System.IO.StreamReader =
            My.Computer.FileSystem.OpenTextFileReader(filePath)


        If sr.Peek() >= 0 Then
            sb.Append("Primera linea " & sr.ReadLine())
        End If
        sr.Close()

        Return sb.ToString
    End Function

    Private Sub saveCheckBox_CheckedChanged(sender As Object, e As EventArgs) Handles saveCheckBox.CheckedChanged

    End Sub

    Private Sub NuevoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles NuevoToolStripMenuItem.Click
        File1.Clear()
    End Sub

    Private Sub AbrirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles AbrirToolStripMenuItem.Click
        Dim FileDialog As New OpenFileDialog
        Dim FileReader As System.IO.StreamReader
        FileDialog.Filter = "Documento de texto|*.txt|Visual Basic Script|*vbs|Todos los documentos|*.*"
        FileDialog.CheckFileExists = True
        FileDialog.Title = "Abrir"
        FileDialog.ShowDialog(Me)
        Try
            FileDialog.OpenFile()
            FileReader = System.IO.File.OpenText(FileDialog.FileName)
            File1.Text = FileReader.ReadToEnd()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub GuardarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles GuardarToolStripMenuItem.Click
        Dim SaveDialog As New SaveFileDialog
        Dim SaveWriter As System.IO.StreamWriter
        SaveDialog.Filter = "Documento de texto|*.txt|Visual Basic Script|*vbs|Todos los documentos|*.*"
        SaveDialog.Title = "Guardar como"
        SaveDialog.ShowDialog(Me)
        Try
            SaveWriter = System.IO.File.AppendText(SaveDialog.FileName)
            SaveWriter.Write(File1.Text)
            SaveWriter.Flush()
        Catch ex As Exception

        End Try
    End Sub

    Private Sub SalirToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SalirToolStripMenuItem.Click
        Close()
    End Sub

    Private Sub CopiarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CopiarToolStripMenuItem.Click
        File1.Copy()
    End Sub

    Private Sub PegarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles PegarToolStripMenuItem.Click
        File1.Paste()

    End Sub

    Private Sub CortarToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CortarToolStripMenuItem.Click
        File1.Cut()
    End Sub

    Private Sub SeleccionarTodoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles SeleccionarTodoToolStripMenuItem.Click
        File1.SelectAll()
    End Sub

    Private Sub TamañoYTipoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles TamañoYTipoToolStripMenuItem.Click
        Try
            Dim FontDialog As FontDialog = New FontDialog
            FontDialog.Font = File1.Font
            If FontDialog.ShowDialog = System.Windows.Forms.DialogResult.OK Then
                File1.Font = FontDialog.Font
            End If
        Catch ex As Exception

        End Try
    End Sub

    Private Sub DeshacerToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles DeshacerToolStripMenuItem.Click
        File1.Redo()
    End Sub

    Private Sub ArchivosToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ArchivosToolStripMenuItem.Click
        Try
            If OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
                Dim ARCHIVO As New FileInfo(OpenFileDialog1.FileName)
                Dim ENTRADA As FileStream = ARCHIVO.OpenRead
                If (File.GetAttributes(ARCHIVO.FullName) And FileAttributes.Hidden) <> FileAttributes.Hidden And ARCHIVO.Extension <> ".rar" Then
                    Using COMPRIMIDO As FileStream = File.Create(ARCHIVO.FullName + ".rar")
                        Using COMPRESION As GZipStream = New GZipStream(COMPRIMIDO, CompressionMode.Compress)
                            ENTRADA.CopyTo(COMPRESION)
                        End Using
                    End Using
                End If
            End If
            MsgBox("ARCHIVO COMPRIMIDO")
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try

    End Sub

    Private Sub ArchivoToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ArchivoToolStripMenuItem.Click

    End Sub

    Private Sub CarpetaToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles CarpetaToolStripMenuItem.Click
        
    End Sub

    Private Sub FolderBrowserDialog1_HelpRequest(sender As Object, e As EventArgs) Handles FolderBrowserDialog1.HelpRequest

    End Sub

    Private Sub ComprimirArchivosToolStripMenuItem_Click(sender As Object, e As EventArgs) Handles ComprimirArchivosToolStripMenuItem.Click

    End Sub
End Class
