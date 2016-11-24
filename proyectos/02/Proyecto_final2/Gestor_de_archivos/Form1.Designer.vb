<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.ButtonARCHIVOCOM = New System.Windows.Forms.Button()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.ButtonARCHIVODESC = New System.Windows.Forms.Button()
        Me.ButtonCARPETADESC = New System.Windows.Forms.Button()
        Me.ButtonCARPETACOM = New System.Windows.Forms.Button()
        Me.FolderBrowserDialog1 = New System.Windows.Forms.FolderBrowserDialog()
        Me.SuspendLayout()
        '
        'ButtonARCHIVOCOM
        '
        Me.ButtonARCHIVOCOM.BackColor = System.Drawing.Color.Black
        Me.ButtonARCHIVOCOM.ForeColor = System.Drawing.Color.Aqua
        Me.ButtonARCHIVOCOM.Location = New System.Drawing.Point(13, 13)
        Me.ButtonARCHIVOCOM.Name = "ButtonARCHIVOCOM"
        Me.ButtonARCHIVOCOM.Size = New System.Drawing.Size(140, 40)
        Me.ButtonARCHIVOCOM.TabIndex = 0
        Me.ButtonARCHIVOCOM.Text = "COMPRIMIR ARCHIVO"
        Me.ButtonARCHIVOCOM.UseVisualStyleBackColor = False
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'ButtonARCHIVODESC
        '
        Me.ButtonARCHIVODESC.BackColor = System.Drawing.Color.Black
        Me.ButtonARCHIVODESC.ForeColor = System.Drawing.Color.Aqua
        Me.ButtonARCHIVODESC.Location = New System.Drawing.Point(175, 12)
        Me.ButtonARCHIVODESC.Name = "ButtonARCHIVODESC"
        Me.ButtonARCHIVODESC.Size = New System.Drawing.Size(140, 40)
        Me.ButtonARCHIVODESC.TabIndex = 1
        Me.ButtonARCHIVODESC.Text = "DESCOMPRIMIR ARCHIVO"
        Me.ButtonARCHIVODESC.UseVisualStyleBackColor = False
        '
        'ButtonCARPETADESC
        '
        Me.ButtonCARPETADESC.BackColor = System.Drawing.Color.Black
        Me.ButtonCARPETADESC.ForeColor = System.Drawing.Color.Aqua
        Me.ButtonCARPETADESC.Location = New System.Drawing.Point(175, 70)
        Me.ButtonCARPETADESC.Name = "ButtonCARPETADESC"
        Me.ButtonCARPETADESC.Size = New System.Drawing.Size(140, 40)
        Me.ButtonCARPETADESC.TabIndex = 3
        Me.ButtonCARPETADESC.Text = "DESCOMPRIMIR CARPETA"
        Me.ButtonCARPETADESC.UseVisualStyleBackColor = False
        '
        'ButtonCARPETACOM
        '
        Me.ButtonCARPETACOM.BackColor = System.Drawing.Color.Black
        Me.ButtonCARPETACOM.ForeColor = System.Drawing.Color.Aqua
        Me.ButtonCARPETACOM.Location = New System.Drawing.Point(13, 71)
        Me.ButtonCARPETACOM.Name = "ButtonCARPETACOM"
        Me.ButtonCARPETACOM.Size = New System.Drawing.Size(140, 40)
        Me.ButtonCARPETACOM.TabIndex = 2
        Me.ButtonCARPETACOM.Text = "COMPRIMIR CARPETA"
        Me.ButtonCARPETACOM.UseVisualStyleBackColor = False
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(9.0!, 16.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackColor = System.Drawing.Color.Black
        Me.ClientSize = New System.Drawing.Size(336, 126)
        Me.Controls.Add(Me.ButtonCARPETADESC)
        Me.Controls.Add(Me.ButtonCARPETACOM)
        Me.Controls.Add(Me.ButtonARCHIVODESC)
        Me.Controls.Add(Me.ButtonARCHIVOCOM)
        Me.Font = New System.Drawing.Font("Microsoft Sans Serif", 9.75!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.ForeColor = System.Drawing.Color.Aqua
        Me.Margin = New System.Windows.Forms.Padding(4)
        Me.MaximizeBox = False
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "COMPRESION - DESCOMPRESION"
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents ButtonARCHIVOCOM As System.Windows.Forms.Button
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents ButtonARCHIVODESC As System.Windows.Forms.Button
    Friend WithEvents ButtonCARPETADESC As System.Windows.Forms.Button
    Friend WithEvents ButtonCARPETACOM As System.Windows.Forms.Button
    Friend WithEvents FolderBrowserDialog1 As System.Windows.Forms.FolderBrowserDialog

End Class
