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
        Me.saveCheckBox = New System.Windows.Forms.CheckBox()
        Me.FolderBrowserDialog1 = New System.Windows.Forms.FolderBrowserDialog()
        Me.filesListBox = New System.Windows.Forms.ListBox()
        Me.browseButton1 = New System.Windows.Forms.Button()
        Me.examineButton2 = New System.Windows.Forms.Button()
        Me.SuspendLayout()
        '
        'saveCheckBox
        '
        Me.saveCheckBox.AutoSize = True
        Me.saveCheckBox.Location = New System.Drawing.Point(12, 126)
        Me.saveCheckBox.Name = "saveCheckBox"
        Me.saveCheckBox.Size = New System.Drawing.Size(81, 17)
        Me.saveCheckBox.TabIndex = 0
        Me.saveCheckBox.Text = "CheckBox1"
        Me.saveCheckBox.UseVisualStyleBackColor = True
        '
        'filesListBox
        '
        Me.filesListBox.FormattingEnabled = True
        Me.filesListBox.Location = New System.Drawing.Point(12, 12)
        Me.filesListBox.Name = "filesListBox"
        Me.filesListBox.Size = New System.Drawing.Size(260, 108)
        Me.filesListBox.TabIndex = 1
        '
        'browseButton1
        '
        Me.browseButton1.Location = New System.Drawing.Point(12, 159)
        Me.browseButton1.Name = "browseButton1"
        Me.browseButton1.Size = New System.Drawing.Size(90, 23)
        Me.browseButton1.TabIndex = 2
        Me.browseButton1.Text = "Seleccionar dir"
        Me.browseButton1.UseVisualStyleBackColor = True
        '
        'examineButton2
        '
        Me.examineButton2.Location = New System.Drawing.Point(131, 159)
        Me.examineButton2.Name = "examineButton2"
        Me.examineButton2.Size = New System.Drawing.Size(75, 23)
        Me.examineButton2.TabIndex = 3
        Me.examineButton2.Text = "Button2"
        Me.examineButton2.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(284, 261)
        Me.Controls.Add(Me.examineButton2)
        Me.Controls.Add(Me.browseButton1)
        Me.Controls.Add(Me.filesListBox)
        Me.Controls.Add(Me.saveCheckBox)
        Me.Name = "Form1"
        Me.Text = "Form1"
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents saveCheckBox As System.Windows.Forms.CheckBox
    Friend WithEvents FolderBrowserDialog1 As System.Windows.Forms.FolderBrowserDialog
    Friend WithEvents filesListBox As System.Windows.Forms.ListBox
    Friend WithEvents browseButton1 As System.Windows.Forms.Button
    Friend WithEvents examineButton2 As System.Windows.Forms.Button

End Class
