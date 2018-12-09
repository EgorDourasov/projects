import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { TabsComponent } from './tabs/tabs.component';
import { ListComponent } from './list/list.component';
import { ItemComponent } from './item/item.component';
import { StarWarsService } from './star-wars.service';

@NgModule({
  declarations: [
    AppComponent,
    TabsComponent,
    ListComponent,
    ItemComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule
  ],
  providers: [StarWarsService],
  bootstrap: [AppComponent]
})
export class AppModule { }
