Imports System.IO
Imports System.IO.Compression

Public Class Form1

    Private Sub ButtonARCHIVOCOM_Click(sender As Object, e As EventArgs) Handles ButtonARCHIVOCOM.Click
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

    Private Sub ButtonARCHIVODESC_Click(sender As Object, e As EventArgs) Handles ButtonARCHIVODESC.Click
        Try
            If OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
                Dim ARCHIVO As New FileInfo(OpenFileDialog1.FileName)
                Using ENTRADA As FileStream = ARCHIVO.OpenRead()
                    Dim NOMBREARCHIVO As String = ARCHIVO.FullName
                    Dim NUEVOARCHIVO = NOMBREARCHIVO.Remove(NOMBREARCHIVO.Length - ARCHIVO.Extension.Length)
                    Using DESCOMPRIMIDO As FileStream = File.Create(NUEVOARCHIVO)
                        Using DESCOMPRESION As GZipStream = New GZipStream(ENTRADA, CompressionMode.Decompress)
                            DESCOMPRESION.CopyTo(DESCOMPRIMIDO)
                        End Using
                    End Using
                End Using
            End If
            MsgBox("ARCHIVO DESCOMPRIMIDO")
        Catch ex As Exception
            MsgBox(ex.Message)
        End Try      
    End Sub

    Private Sub ButtonCARPETACOM_Click(sender As Object, e As EventArgs) Handles ButtonCARPETACOM.Click
        If FolderBrowserDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
            Try
                ZipFile.CreateFromDirectory(FolderBrowserDialog1.SelectedPath, FolderBrowserDialog1.SelectedPath & ".zip")
                MsgBox("CARPETA COMPRIMIDA")
            Catch ex As Exception
                MsgBox(ex.Message)
            End Try
        End If
    End Sub

    Private Sub ButtonCARPETADESC_Click(sender As Object, e As EventArgs) Handles ButtonCARPETADESC.Click
        If OpenFileDialog1.ShowDialog = Windows.Forms.DialogResult.OK Then
            Try
                ZipFile.ExtractToDirectory(OpenFileDialog1.FileName, OpenFileDialog1.FileName.Substring(0, OpenFileDialog1.FileName.LastIndexOf(".")))
                MsgBox("CARPETA DESCOMPRIMIDA")
            Catch ex As Exception
                MsgBox(ex.Message)
            End Try
        End If 
    End Sub
End Class
