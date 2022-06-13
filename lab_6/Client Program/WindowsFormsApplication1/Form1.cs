using System;
using System.Data;
using System.Linq;
using System.Windows.Forms;
using System.IO.Ports;
using System.Drawing;
using System.Threading;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using System.Text;

namespace WindowsFormsApplication1 {
    public partial class Form1 : Form
    {      
        public Form1()
        {
            InitializeComponent();
        }

        private void ComportSelectionBox_Click(object sender, EventArgs e)
        {
            int num;
            ComportSelectionBox.Items.Clear();
            string[] ports = SerialPort.GetPortNames().OrderBy(a => a.Length > 3 && int.TryParse(a.Substring(3), out num) ? num : 0).ToArray();
            ComportSelectionBox.Items.AddRange(ports);
        }

        private void OpenPortButton_Click(object sender, EventArgs e)
        {
            if (!SerialPort1.IsOpen)
            {
                try
                {
                    SerialPort1.PortName = ComportSelectionBox.Text;
                    SerialPort1.Open();
                    OpenPortButton.Text = "Close";
                    ComportSelectionBox.Enabled = false;
                    ButtonGetInfoFromSlave1.Visible = true;
                    ButtonGetInfoFromSlave2.Visible = true;
                }
                catch
                {
                    MessageBox.Show("Port " + ComportSelectionBox.Text + " is invalid!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                SerialPort1.Close();
                OpenPortButton.Text = "Open";
                ComportSelectionBox.Enabled = true;
                ButtonGetInfoFromSlave1.Visible = false;
                ButtonGetInfoFromSlave2.Visible = false;
            }
        }

        private void ButtonGetInfoFromSlave1_Click(object sender, EventArgs e)
        {
            ButtonGetInfoFromSlave1.Enabled = false;
            ButtonGetInfoFromSlave2.Enabled = false;

            byte[] requestInfo = new byte[2];
            requestInfo[0] = 0xA1;
            SerialPort1.Write(requestInfo, 0, 1);
            byte responseCode = (byte)SerialPort1.ReadByte();
            if (responseCode == 0xA1)
            {
                byte[] buffer = new byte[50];
                for (int i = 0; i < 50; i++)
                {
                    byte receivedByte = (byte)SerialPort1.ReadByte();
                    buffer[i] = receivedByte;
                }
                Slave1InfoTextField.Text = System.Text.Encoding.UTF8.GetString(buffer, 0, buffer.Length);
                byte isDistorted = (byte)SerialPort1.ReadByte();
                if (isDistorted == 0x01)
                {
                    Slave1InfoStatusLabel.Text = "Signal is distorted";
                    Slave1InfoStatusLabel.ForeColor = Color.Red;
                } else
                {
                    Slave1InfoStatusLabel.Text = "No distortion found";
                    Slave1InfoStatusLabel.ForeColor = Color.Green;
                }
            }
            ButtonGetInfoFromSlave1.Enabled = true;
            ButtonGetInfoFromSlave2.Enabled = true;
        }

        private void ButtonGetInfoFromSlave2_Click(object sender, EventArgs e)
        {
            ButtonGetInfoFromSlave1.Enabled = false;
            ButtonGetInfoFromSlave2.Enabled = false;

            byte[] requestInfo = new byte[2];
            requestInfo[0] = 0xB1;
            SerialPort1.Write(requestInfo, 0, 1);
            byte responseCode = (byte)SerialPort1.ReadByte();
            if (responseCode == 0xB1)
            {
                byte[] buffer = new byte[50];
                for (int i = 0; i < 50; i++)
                {
                    byte receivedByte = (byte)SerialPort1.ReadByte();
                    buffer[i] = receivedByte;
                }
                Slave2InfoTextField.Text = System.Text.Encoding.UTF8.GetString(buffer, 0, buffer.Length);
                byte isDistorted = (byte)SerialPort1.ReadByte();
                if (isDistorted == 0x01)
                {
                    Slave2InfoStatusLabel.Text = "Signal is distorted";
                    Slave2InfoStatusLabel.ForeColor = Color.Red;
                }
                else
                {
                    Slave2InfoStatusLabel.Text = "No distortion found";
                    Slave2InfoStatusLabel.ForeColor = Color.Green;
                }
            }
            ButtonGetInfoFromSlave1.Enabled = true;
            ButtonGetInfoFromSlave2.Enabled = true;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
