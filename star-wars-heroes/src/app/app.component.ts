import { Component, OnInit } from '@angular/core';
import { StarWarsService } from './star-wars.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit{
  title = 'star-wars-heroes';
  swService: StarWarsService;
  constructor(swService: StarWarsService){
    this.swService = swService;
  }

  ngOnInit(){
    this.swService.fetchCharacters();
  }
}
