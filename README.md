# Timers

Nous pouvons utiliser plusiuers timers avec des frequences differentes 

```c
    ALLEGRO_TIMER * secondes;
    ALLEGRO_TIMER * minutes;
    ALLEGRO_TIMER * heures;

    secondes = al_create_timer(1.0);
    minutes = al_create_timer(60.0);
    heures = al_create_timer(3600.0);
```

Il faut enregistrer chaque timer comme source:

```
    al_register_event_source(fifo, al_get_timer_event_source(secondes)); // timer secondes
    al_register_event_source(fifo, al_get_timer_event_source(minutes));  // timer minutes
    al_register_event_source(fifo, al_get_timer_event_source(heures));   // timer heures
```

et au moment de l'indetification de l'événement on peut identifier la source d'un event timer avec `event.timer.source`

```c
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
```



