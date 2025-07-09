using System;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Data;
using Neto.History.ViewModels;

namespace Neto.History
{
    public sealed partial class MainWindow : WinUIEx.WindowEx
    {
        public MainViewModel ViewModel { get; } = new MainViewModel();

        public MainWindow()
        {
            this.InitializeComponent();
            this.ExtendsContentIntoTitleBar = true;

            ClearHistoryButton.IsEnabled = ViewModel.Records.Count > 0;
        }

        private async void ClearHistoryButton_Click(object sender, RoutedEventArgs e)
        {
            ContentDialog confirmationDialog = new ContentDialog
            {
                Title = "Confirm",
                Content = "Are you sure you want to clear history?",
                PrimaryButtonText = "Yes",
                CloseButtonText = "No",
                XamlRoot = ClearHistoryButton.XamlRoot
            };

            ContentDialogResult result = await confirmationDialog.ShowAsync();
            if (result == ContentDialogResult.Primary)
            {
                ViewModel.ClearHistory();
            }

            ClearHistoryButton.IsEnabled = ViewModel.Records.Count > 0;
        }

        private void LoadHistoryButton_Click(object sender, RoutedEventArgs e)
        {
            ViewModel.LoadHistory();

            HistoryTable.ItemsSource = ViewModel.Records;
            ClearHistoryButton.IsEnabled = ViewModel.Records.Count > 0;
        }
    }

    public class BoolToIconConverteer : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return (bool)value ? "\uE73E" : "\uE711";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language) => null;
    }
}
