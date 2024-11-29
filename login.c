#include <gtk/gtk.h>
#include <string.h>
#include "filmes.h"

// Função chamada quando o botão "Login" é clicado
void on_login_button_clicked(GtkWidget *widget, gpointer data) {
    GtkEntry **entries = (GtkEntry **)data;
    const char *username = gtk_entry_get_text(entries[0]);
    const char *password = gtk_entry_get_text(entries[1]);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Login bem-sucedido!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        // Aqui você pode continuar para a tela principal do programa
        // Exemplo: chamar a função principal do sistema de filmes
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK, "Usuário ou senha incorretos!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void exibirTelaLogin() {
    GtkWidget *window, *grid, *label_user, *label_pass, *entry_user, *entry_pass, *button_login;

    gtk_init(NULL, NULL);

    // Janela principal
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tela de Login");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Layout (Grade)
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Labels
    label_user = gtk_label_new("Usuário:");
    label_pass = gtk_label_new("Senha:");

    // Campos de entrada
    entry_user = gtk_entry_new();
    entry_pass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(entry_pass), FALSE); // Ocultar texto da senha

    // Botão de login
    button_login = gtk_button_new_with_label("Login");

    // Adicionar widgets à grade
    gtk_grid_attach(GTK_GRID(grid), label_user, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_user, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), label_pass, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_pass, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button_login, 1, 2, 1, 1);

    // Conectar sinal ao botão de login
    GtkEntry *entries[2] = {GTK_ENTRY(entry_user), GTK_ENTRY(entry_pass)};
    g_signal_connect(button_login, "clicked", G_CALLBACK(on_login_button_clicked), entries);

    // Exibir tudo
    gtk_widget_show_all(window);

    gtk_main();
}