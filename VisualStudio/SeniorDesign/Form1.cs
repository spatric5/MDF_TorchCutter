using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SeniorDesign
{
    public partial class Form1 : Form
    {
        private bool upClicked = false;
        private bool downClicked = false;
        private bool inClicked = false;
        private bool outClicked = false;
        private bool arduinoConnected = false;

        public Form1()
        {
            InitializeComponent();
            try
            {
                serialPort1.Open();
                arduinoConnected = true;
            }
            catch
            {
                MessageBox.Show("Arduino Not Connected.");
                arduinoConnected = false;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
            {
                if (downClicked)
                    serialPort1.Write("s");
                else
                    serialPort1.Write("d");
            }
            downClicked = !downClicked;
            return;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
            {
                if (inClicked)
                    serialPort1.Write("k");
                else
                    serialPort1.Write("i");
            }
            inClicked = !inClicked;
            return;
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
            {
                if (outClicked)
                    serialPort1.Write("p");
                else
                    serialPort1.Write("o");
            }
            outClicked = !outClicked;
            return;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
            {
                if (upClicked)
                    serialPort1.Write("y");
                else
                    serialPort1.Write("u");
            }
            upClicked = !upClicked;
            return;
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            System.Threading.Thread.Sleep(60);
            string position = serialPort1.ReadExisting();
            if (position.Contains("\r\n"))
                position = position.Replace("\r\n", string.Empty);
            SetText(position.ToString());

        }

        delegate void SetTextCallback(string text);

        private void SetText(string text)
        {
            // InvokeRequired required compares the thread ID of the
            // calling thread to the thread ID of the creating thread.
            // If these threads are different, it returns true.
            if (this.textBox1.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                this.textBox1.Text = text;
            }
        }
    }
}
