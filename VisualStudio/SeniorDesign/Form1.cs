using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
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
        public readonly BackgroundWorker worker = new BackgroundWorker();

        public Form1()
        {
            InitializeComponent();
            try
            {
                worker.DoWork += worker_DoWork;
                worker.WorkerSupportsCancellation = true;
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
            if(text[0] == 'l')
            {
                if (this.textBox5.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    this.Invoke(d, new object[] { text });
                }
                else
                {
                    this.textBox5.Text = text;
                }
            }
            else if(text[0] == 't')
            {
                if (this.textBox4.InvokeRequired)
                {
                    SetTextCallback d = new SetTextCallback(SetText);
                    this.Invoke(d, new object[] { text });
                }
                else
                {
                    this.textBox4.Text = text;
                }
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("q");
            return;
        }

        private void button13_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("w");
            return;
        }

        private void button14_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("y");
            return;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("z");
            return;
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("1");
            return;
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("2");
            return;
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("3");
            return;
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("b");
            return;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("f");
            return;
        }

        private void button15_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("zz2332yyff");
            return;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("zz2332yyffzz2332yyff");
            return;
        }

        private void button18_Click(object sender, EventArgs e)
        {
            if (arduinoConnected)
                serialPort1.Write("zz2332yyffzz2332yyffzz2332yyff");
            return;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            worker.RunWorkerAsync();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            worker.CancelAsync();
        }

        private void worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (!worker.CancellationPending)
            {
                //DateTime startT = DateTime.Now;
                //string t = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss");
                //if (textBox5.InvokeRequired)
                //textBox5.Invoke(new MethodInvoker(delegate { textBox5.Text = t; }));
                if (arduinoConnected)
                    serialPort1.Write("c");
                System.Threading.Thread.Sleep(6000);
                //DateTime endT = DateTime.Now;
                //string lengthOfTime = (endT - startT).ToString();
                //if (textBox4.InvokeRequired)
                    //textBox4.Invoke(new MethodInvoker(delegate { textBox4.Text = lengthOfTime; }));
            }
        }
    }
}
