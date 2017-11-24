#define SERIAL

using System;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;


namespace LightsController
{
    public partial class Form1 : Form
    {
        private static SerialPort port;
        private static bool _continue;
        private static Thread readThread;

        public Form1()
        {
            port = null;

            _continue = false;
            readThread = null;
            InitializeComponent();
        }

        private void radioButton_CheckedChanged(object sender, EventArgs e)
        {
            var button = sender as RadioButton;
            if (button == null || !button.Checked)
            {
                return;
            }
            Console.WriteLine("Option: " + button.Name);
            if (port == null)
            {
                return;
            }

#if SERIAL
            try
            {
                port.WriteLine("^" + button.Name + "$");
            }
            catch (TimeoutException error)
            {
                MessageBox.Show(error.Message);
            }
#else
            Console.WriteLine("^" + button.Name + "$");
#endif
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            Console.WriteLine("Ports: ");
            foreach (string port in ports)
            {
                Console.WriteLine(port);
            }

            cbboxPorts.DataSource = ports;
        }

        private void cbboxPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            var box = sender as ComboBox;
            if (box == null || (string)box.SelectedItem == "")
            {
                return;
            }

            string portName = box.SelectedItem as string;
            Console.WriteLine("Selected: " + portName);
            display_message("Selected: " + portName);
            clear_port();

            port = new SerialPort(portName, 9600);
            port.ReadTimeout = 500;
            port.WriteTimeout = 500;
            port.Encoding = Encoding.Default;
#if SERIAL
            port.Open();
            Console.WriteLine("Port Opened");
            display_message("Port Opened");
#endif
            _continue = true;
#if SERIAL
            readThread = new Thread(Read);
            readThread.Start();
#endif        
        }

        private void Read()
        {
            while (_continue)
            {
                try
                {
                    while (true)
                    {
                        string message = port.ReadLine();
                        Console.WriteLine(message);
                        display_message(message);
                    }
                }
                catch (TimeoutException) { }
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            clear_port();
        }

        void clear_port()
        {
            _continue = false;
            if (readThread != null)
            {
                readThread.Join();
            }
            if (port != null)
            {
                port.Close();
            }
            display_message("Disconnected");
        }

        void display_message(string message)
        {
            if (lblResponse.InvokeRequired)
            {
                this.Invoke((MethodInvoker)delegate { lblResponse.Text = message; });
            }
            else
            {
                lblResponse.Text = message;
            }
        }
    }
}
