#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int main() {
    // declarations
    ALLEGRO_DISPLAY * game_display;
    ALLEGRO_TIMER * game_timer;
    ALLEGRO_EVENT_QUEUE * fifo;
    ALLEGRO_EVENT event;
    bool fini = false;
    ALLEGRO_FONT * orbitron;
    // on utilise trois timers uniquement pour des raisons pedagogiques
    // car le timer des secondes est suffisant
    ALLEGRO_TIMER * secondes;
    ALLEGRO_TIMER * minutes;
    ALLEGRO_TIMER * heures;
    int s,m,h;

    // initialisation
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());
    assert(al_init_font_addon());
    assert(al_init_ttf_addon());

    // Creation
    // al_create_*
    game_display = al_create_display(800, 600);
    game_timer = al_create_timer(1.0/24.0);
    secondes = al_create_timer(1.0);
    minutes = al_create_timer(60.0);
    heures = al_create_timer(3600.0);
    fifo = al_create_event_queue();
    orbitron = al_load_ttf_font("../Orbitron/static/Orbitron-Black.ttf",60,ALLEGRO_ALIGN_LEFT);
    assert(orbitron);
    s=m=h=0;

    // Sources
    al_register_event_source(fifo, al_get_display_event_source(game_display)); // display
    al_register_event_source(fifo, al_get_timer_event_source(game_timer)); // timer global
    al_register_event_source(fifo, al_get_timer_event_source(secondes)); // timer secondes
    al_register_event_source(fifo, al_get_timer_event_source(minutes));  // timer minutes
    al_register_event_source(fifo, al_get_timer_event_source(heures));   // timer heures
    al_register_event_source(fifo, al_get_keyboard_event_source());

    // boucle d'events
    al_start_timer(game_timer);
    al_start_timer(secondes);
    al_start_timer(minutes);
    al_start_timer(heures);
    while (!fini){
        al_wait_for_event(fifo, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ESCAPE:
                        fini = true;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER:

               if(event.timer.source == secondes) {
                   s++;
                   if (s>59){
                       s = 0;
                   }
                }
                if(event.timer.source == minutes) {
                    m++;
                    if (m>59){
                        m = 0;
                    }
                }
                if(event.timer.source == heures ){
                    h++;
                    if (h>23){
                        h = 0;
                    }
                }

                if(event.timer.source == game_timer) {
                    al_clear_to_color(al_map_rgb(255,255,255));
                    al_draw_textf(orbitron,al_map_rgb(0,0,0),300,200,ALLEGRO_ALIGN_LEFT,"%d:%d:%d",h,m,s);
                    al_flip_display();
                }

                break;
        }
    }


    // liberation
    al_destroy_display(game_display);
    al_destroy_timer(game_timer);
    al_destroy_timer(secondes);
    al_destroy_timer(minutes);
    al_destroy_timer(heures);
    al_destroy_event_queue(fifo);

    return 0;
}
