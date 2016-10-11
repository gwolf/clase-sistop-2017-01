Public Class Form1
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        Timer1.Start() ' Iniciar el Timer
        TextBox1.Text = My.Computer.Name ' Nos devuelve el nombre del equipo.
        TextBox2.Text = My.User.Name 'Nos devuelve el nombre de Usuario actual + equipo.
        TextBox3.Text = My.Computer.Info.OSFullName ' Nos devuelve el nombre completo del sistema operativo.
        TextBox4.Text = My.Computer.Info.OSPlatform ' Nos devuelce el tipo de plataforma en la que trabaj nuestro sistema operativo.
        TextBox5.Text = My.Computer.Info.OSVersion 'Nos devuelve la versión del sistema operativo.
        TextBox6.Text = System.DateTime.Now 'Nos devuelve la hora y la fecha en formtao 00/00/0000.
        TextBox7.Text = System.DateTime.Today 'Nos devuelve la fecha en formato 00/00/0000.
        '  TextBox9.Text = My.Application.Info.Title 'Nos devuelve el titulo de la aplicación.
        ' TextBox10.Text = My.Application.Info.CompanyName 'Nos devuelve la compañia que fabricó la aplicación.
        'TextBox11.Text = My.Application.Info.Version.ToString ' Nos devuleva la versión de la aplicación
        TextBox12.Text = System.Environment.ProcessorCount ' Nos devuelve el numero de procesadores que tenemos en el pc.
        TextBox13.Text = System.Environment.UserName ' Nos devuelve el Nombre de Usuario.
        TextBox14.Text = System.Environment.UserDomainName 'Nos devuelve el nombre del dominio de red.
        TextBox15.Text = System.Environment.OSVersion.ToString ' No devuelve la versón del sistema completa
        TextBox16.Text = System.Environment.SystemDirectory ' 'Nos devuelve el directorio del sistema.
        TextBox20.Text = My.Application.UICulture.ToString 'Nos devuelve la configuración Regional.
        TextBox21.Text = System.Globalization.CultureInfo.InstalledUICulture.ToString 'Nos devuelve el idioma de instalación del sistema operativo.
        TextBox22.Text = System.Globalization.RegionInfo.CurrentRegion.DisplayName 'Nos devuelva el nombre de la region actual
        'TextBox23.Text = System.Globalization.RegionInfo.CurrentRegion.GeoId 'Nos devuelve la Geolocalización. 
        TextBox24.Text = System.Globalization.RegionInfo.CurrentRegion.EnglishName 'Nos devuelve el nombre del país o región en inglés.
        'TextBox25.Text = System.Globalization.RegionInfo.CurrentRegion.CurrencyNativeName 'Nos devuelve el valor del tipo de moneda.
        'TextBox26.Text = System.Globalization.RegionInfo.CurrentRegion.CurrencySymbol 'Nos devuelve el simbolo de la moneda.
        TextBox27.Text = System.Globalization.RegionInfo.CurrentRegion.TwoLetterISORegionName ' Nos devuelve el nombre de país o región segun ISO en 2 letras.
        TextBox28.Text = System.Globalization.RegionInfo.CurrentRegion.ThreeLetterWindowsRegionName 'Nos devuelve el nombre de país o región segun windows y en 3 letras.
        TextBox29.Text = System.Globalization.RegionInfo.CurrentRegion.ThreeLetterISORegionName ' Nos devuelve el nombre de país o region segun ISO en 3 letras
        '.Text = System.Globalization.RegionInfo.CurrentRegion.ISOCurrencySymbol 'Nos de devuelve le symbolo de nuestra moneda segun ISO
        TextBox31.Text = My.Computer.Registry.CurrentUser.ToString 'Nos devuelve la rama Current_User del registro de Windows
        TextBox32.Text = My.Computer.Registry.LocalMachine.ToString 'Nos devuelve la rama Local_Machine del registro de Windows
        TextBox33.Text = My.Computer.Registry.CurrentConfig.ToString 'Nos devuelve la rama Current_Config del registro de Windows
        TextBox34.Text = My.Computer.Registry.ClassesRoot.ToString 'Nos devuelve la rama Classes_Root del registro de Windows


        'Nos devuelve el valor de si hay internet o no
        If My.Computer.Network.IsAvailable Then
            TextBox8.Text = "Estás conectado a Internet"
        Else

            TextBox8.Text = "No estás Conectado a Internet"
        End If
        'Comprueba si el ratón dispone de rueda
        If My.Computer.Mouse.WheelExists = True Then
            TextBox17.Text = "Su ratón dispone de rueda"
        Else
            TextBox17.Text = "Su ratón no disponde de rueda"
        End If
        'Esto verifica si el ratón tiene los botones intercambiados
        If My.Computer.Mouse.ButtonsSwapped = True Then
            TextBox19.Text = "Los botones del ratón están intercanviados"
        Else
            TextBox19.Text = "Los botones del ratón no están intercanviados"
        End If

    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        TextBox6.Text = System.DateTime.Now
    End Sub
End Class
