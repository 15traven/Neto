using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Neto.History.ViewModels
{
    public class MainViewModel
    {
        public ObservableCollection<Record> Records { get; set; }
        
        public MainViewModel()
        {
            LoadHistory();
        }

        public void LoadHistory()
        {
            string historyFilePath = Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
                "Neto",
                "history.json");

            if (!File.Exists(historyFilePath))
            {
                Records = [];
            }
            else
            {
                string fileContents = File.ReadAllText(historyFilePath);
                List<Record> list = JsonSerializer.Deserialize<List<Record>>(
                    fileContents, 
                    new JsonSerializerOptions()
                    {
                        PropertyNameCaseInsensitive = true
                    });
                Records = new ObservableCollection<Record>(list ?? []);
            }
        }

        public void ClearHistory()
        {
            Records.Clear();

            string historyFilePath = Path.Combine(
                Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),
                "Neto",
                "history.json");

            if (File.Exists(historyFilePath))
            {
                File.WriteAllText(historyFilePath, "[]");
            }
        }
    }

    public partial class Record : INotifyPropertyChanged
    {
        private string _date;
        private string _time;
        private bool _status;

        [JsonPropertyName("date")]
        public string Date
        {
            get => _date;
            set
            {
                _date = value;
                OnPropertyChanged(nameof(Date));
            }
        }
        [JsonPropertyName("time")]
        public string Time
        {
            get => _time;
            set
            {
                _time = value;
                OnPropertyChanged(nameof(Time));
            }
        }
        [JsonPropertyName("status")]
        public bool Status
        {
            get => _status;
            set
            {
                _status = value;
                OnPropertyChanged(nameof(Status));
            }
        }

        private void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public event PropertyChangedEventHandler PropertyChanged;
    }
}
