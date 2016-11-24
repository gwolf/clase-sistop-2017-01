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
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.saveCheckBox = New System.Windows.Forms.CheckBox()
        Me.FolderBrowserDialog1 = New System.Windows.Forms.FolderBrowserDialog()
        Me.filesListBox = New System.Windows.Forms.ListBox()
        Me.browseButton1 = New System.Windows.Forms.Button()
        Me.examineButton2 = New System.Windows.Forms.Button()
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.ArchivoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NuevoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AbrirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GuardarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SalirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopiarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PegarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CortarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SeleccionarTodoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.DeshacerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.FuentaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.TamañoYTipoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.OpcinesRARToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ComprimirArchivosToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ArchivosToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CarpetaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.DescomprimirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.File1 = New System.Windows.Forms.RichTextBox()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.OpenFileDialog1 = New System.Windows.Forms.OpenFileDialog()
        Me.OpenFileDialog2 = New System.Windows.Forms.OpenFileDialog()
        Me.FolderBrowserDialog2 = New System.Windows.Forms.FolderBrowserDialog()
        Me.MenuStrip1.SuspendLayout()
        Me.SuspendLayout()
        '
        'saveCheckBox
        '
        Me.saveCheckBox.AutoSize = True
        Me.saveCheckBox.Location = New System.Drawing.Point(12, 168)
        Me.saveCheckBox.Name = "saveCheckBox"
        Me.saveCheckBox.Size = New System.Drawing.Size(137, 17)
        Me.saveCheckBox.TabIndex = 0
        Me.saveCheckBox.Text = "Guardar datos en un txt"
        Me.saveCheckBox.UseVisualStyleBackColor = True
        '
        'FolderBrowserDialog1
        '
        '
        'filesListBox
        '
        Me.filesListBox.FormattingEnabled = True
        Me.filesListBox.Location = New System.Drawing.Point(12, 54)
        Me.filesListBox.Name = "filesListBox"
        Me.filesListBox.Size = New System.Drawing.Size(407, 108)
        Me.filesListBox.TabIndex = 1
        '
        'browseButton1
        '
        Me.browseButton1.Location = New System.Drawing.Point(12, 191)
        Me.browseButton1.Name = "browseButton1"
        Me.browseButton1.Size = New System.Drawing.Size(124, 23)
        Me.browseButton1.TabIndex = 2
        Me.browseButton1.Text = "Seleccionar directorio"
        Me.browseButton1.UseVisualStyleBackColor = True
        '
        'examineButton2
        '
        Me.examineButton2.Location = New System.Drawing.Point(142, 191)
        Me.examineButton2.Name = "examineButton2"
        Me.examineButton2.Size = New System.Drawing.Size(95, 23)
        Me.examineButton2.TabIndex = 3
        Me.examineButton2.Text = "Ver informacion"
        Me.examineButton2.UseVisualStyleBackColor = True
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ArchivoToolStripMenuItem, Me.EToolStripMenuItem, Me.FuentaToolStripMenuItem, Me.OpcinesRARToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(1000, 24)
        Me.MenuStrip1.TabIndex = 4
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'ArchivoToolStripMenuItem
        '
        Me.ArchivoToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NuevoToolStripMenuItem, Me.AbrirToolStripMenuItem, Me.GuardarToolStripMenuItem, Me.SalirToolStripMenuItem})
        Me.ArchivoToolStripMenuItem.Name = "ArchivoToolStripMenuItem"
        Me.ArchivoToolStripMenuItem.Size = New System.Drawing.Size(60, 20)
        Me.ArchivoToolStripMenuItem.Text = "Archivo"
        '
        'NuevoToolStripMenuItem
        '
        Me.NuevoToolStripMenuItem.Name = "NuevoToolStripMenuItem"
        Me.NuevoToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.NuevoToolStripMenuItem.Text = "Nuevo"
        '
        'AbrirToolStripMenuItem
        '
        Me.AbrirToolStripMenuItem.Name = "AbrirToolStripMenuItem"
        Me.AbrirToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.AbrirToolStripMenuItem.Text = "Abrir"
        '
        'GuardarToolStripMenuItem
        '
        Me.GuardarToolStripMenuItem.Name = "GuardarToolStripMenuItem"
        Me.GuardarToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.GuardarToolStripMenuItem.Text = "Guardar"
        '
        'SalirToolStripMenuItem
        '
        Me.SalirToolStripMenuItem.Name = "SalirToolStripMenuItem"
        Me.SalirToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.SalirToolStripMenuItem.Text = "Salir"
        '
        'EToolStripMenuItem
        '
        Me.EToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.CopiarToolStripMenuItem, Me.PegarToolStripMenuItem, Me.CortarToolStripMenuItem, Me.SeleccionarTodoToolStripMenuItem, Me.DeshacerToolStripMenuItem})
        Me.EToolStripMenuItem.Name = "EToolStripMenuItem"
        Me.EToolStripMenuItem.Size = New System.Drawing.Size(58, 20)
        Me.EToolStripMenuItem.Text = "Edicion"
        '
        'CopiarToolStripMenuItem
        '
        Me.CopiarToolStripMenuItem.Name = "CopiarToolStripMenuItem"
        Me.CopiarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.CopiarToolStripMenuItem.Text = "Copiar"
        '
        'PegarToolStripMenuItem
        '
        Me.PegarToolStripMenuItem.Name = "PegarToolStripMenuItem"
        Me.PegarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.PegarToolStripMenuItem.Text = "Pegar"
        '
        'CortarToolStripMenuItem
        '
        Me.CortarToolStripMenuItem.Name = "CortarToolStripMenuItem"
        Me.CortarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.CortarToolStripMenuItem.Text = "Cortar"
        '
        'SeleccionarTodoToolStripMenuItem
        '
        Me.SeleccionarTodoToolStripMenuItem.Name = "SeleccionarTodoToolStripMenuItem"
        Me.SeleccionarTodoToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.SeleccionarTodoToolStripMenuItem.Text = "Seleccionar todo"
        '
        'DeshacerToolStripMenuItem
        '
        Me.DeshacerToolStripMenuItem.Name = "DeshacerToolStripMenuItem"
        Me.DeshacerToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.DeshacerToolStripMenuItem.Text = "Deshacer"
        '
        'FuentaToolStripMenuItem
        '
        Me.FuentaToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.TamañoYTipoToolStripMenuItem})
        Me.FuentaToolStripMenuItem.Name = "FuentaToolStripMenuItem"
        Me.FuentaToolStripMenuItem.Size = New System.Drawing.Size(55, 20)
        Me.FuentaToolStripMenuItem.Text = "Fuente"
        '
        'TamañoYTipoToolStripMenuItem
        '
        Me.TamañoYTipoToolStripMenuItem.Name = "TamañoYTipoToolStripMenuItem"
        Me.TamañoYTipoToolStripMenuItem.Size = New System.Drawing.Size(151, 22)
        Me.TamañoYTipoToolStripMenuItem.Text = "Tamaño y tipo"
        '
        'OpcinesRARToolStripMenuItem
        '
        Me.OpcinesRARToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ComprimirArchivosToolStripMenuItem, Me.DescomprimirToolStripMenuItem})
        Me.OpcinesRARToolStripMenuItem.Name = "OpcinesRARToolStripMenuItem"
        Me.OpcinesRARToolStripMenuItem.Size = New System.Drawing.Size(94, 20)
        Me.OpcinesRARToolStripMenuItem.Text = "Opciones RAR"
        '
        'ComprimirArchivosToolStripMenuItem
        '
        Me.ComprimirArchivosToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ArchivosToolStripMenuItem, Me.CarpetaToolStripMenuItem})
        Me.ComprimirArchivosToolStripMenuItem.Name = "ComprimirArchivosToolStripMenuItem"
        Me.ComprimirArchivosToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ComprimirArchivosToolStripMenuItem.Text = "Comprimir "
        '
        'ArchivosToolStripMenuItem
        '
        Me.ArchivosToolStripMenuItem.Name = "ArchivosToolStripMenuItem"
        Me.ArchivosToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ArchivosToolStripMenuItem.Text = "Archivo"
        '
        'CarpetaToolStripMenuItem
        '
        Me.CarpetaToolStripMenuItem.Name = "CarpetaToolStripMenuItem"
        Me.CarpetaToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.CarpetaToolStripMenuItem.Text = "Carpeta"
        '
        'DescomprimirToolStripMenuItem
        '
        Me.DescomprimirToolStripMenuItem.Name = "DescomprimirToolStripMenuItem"
        Me.DescomprimirToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.DescomprimirToolStripMenuItem.Text = "Descomprimir"
        '
        'File1
        '
        Me.File1.Location = New System.Drawing.Point(434, 54)
        Me.File1.Name = "File1"
        Me.File1.Size = New System.Drawing.Size(554, 372)
        Me.File1.TabIndex = 5
        Me.File1.Text = "Ingrese texto "
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(434, 35)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(84, 13)
        Me.Label1.TabIndex = 6
        Me.Label1.Text = "Editar contenido"
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(12, 35)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(174, 13)
        Me.Label2.TabIndex = 7
        Me.Label2.Text = "Contenido del directorio a comprimir"
        '
        'OpenFileDialog1
        '
        Me.OpenFileDialog1.FileName = "OpenFileDialog1"
        '
        'OpenFileDialog2
        '
        Me.OpenFileDialog2.FileName = "OpenFileDialog2"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(1000, 438)
        Me.Controls.Add(Me.Label2)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.File1)
        Me.Controls.Add(Me.examineButton2)
        Me.Controls.Add(Me.browseButton1)
        Me.Controls.Add(Me.filesListBox)
        Me.Controls.Add(Me.saveCheckBox)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.Text = "Gestor de archivos Luna"
        Me.MenuStrip1.ResumeLayout(false)
        Me.MenuStrip1.PerformLayout
        Me.ResumeLayout(false)
        Me.PerformLayout

End Sub
    Friend WithEvents saveCheckBox As System.Windows.Forms.CheckBox
    Friend WithEvents FolderBrowserDialog1 As System.Windows.Forms.FolderBrowserDialog
    Friend WithEvents filesListBox As System.Windows.Forms.ListBox
    Friend WithEvents browseButton1 As System.Windows.Forms.Button
    Friend WithEvents examineButton2 As System.Windows.Forms.Button
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents File1 As System.Windows.Forms.RichTextBox
    Friend WithEvents ArchivoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents FuentaToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents NuevoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AbrirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents GuardarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SalirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CopiarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PegarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CortarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SeleccionarTodoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DeshacerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents TamañoYTipoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents OpcinesRARToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ComprimirArchivosToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ArchivosToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CarpetaToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DescomprimirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenFileDialog1 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents OpenFileDialog2 As System.Windows.Forms.OpenFileDialog
    Friend WithEvents FolderBrowserDialog2 As System.Windows.Forms.FolderBrowserDialog

End Class
